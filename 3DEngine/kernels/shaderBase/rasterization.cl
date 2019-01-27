
float interpolateF(float value1, float value2, float perCent)
{
	return value1 + (value2 - value1)*perCent;
}

void interpolatePI(PixelInputType* output, PixelInputType* lValue, PixelInputType* rValue, float perCent)
{
	int i;
	int size = sizeof(PixelInputType) / sizeof(float);
	float *outputArray, *lValueArray, *rValueArray;
	outputArray = output;
	lValueArray = lValue;
	rValueArray = rValue;
	for (i = 0;i < size;i++)
		outputArray[i] = interpolateF(lValueArray[i], rValueArray[i], perCent);
}
void createDeltaPI(PixelInputType* output, PixelInputType* lValue, PixelInputType* rValue, float steps)
{
	int i;
	int size = sizeof(PixelInputType) / sizeof(float);
	float *outputArray, *lValueArray, *rValueArray;
	outputArray = output;
	lValueArray = lValue;
	rValueArray = rValue;
	for (i = 0;i < size;i++)
		outputArray[i] = (rValueArray[i] - lValueArray[i]) / steps;
}
void addPI(PixelInputType* output, PixelInputType* lValue, PixelInputType* rValue)
{
	int i;
	int size = sizeof(PixelInputType) / sizeof(float);
	float *outputArray, *lValueArray, *rValueArray;
	outputArray = output;
	lValueArray = lValue;
	rValueArray = rValue;
	for (i = 0;i < size;i++)
		outputArray[i] = lValueArray[i] + rValueArray[i];
}
void subPI(PixelInputType* output, PixelInputType* lValue, PixelInputType* rValue)
{
	int i;
	int size = sizeof(PixelInputType) / sizeof(float);
	float *outputArray, *lValueArray, *rValueArray;
	outputArray = output;
	lValueArray = lValue;
	rValueArray = rValue;
	for (i = 0;i < size;i++)
		outputArray[i] = lValueArray[i] - rValueArray[i];
}
void copyPI(PixelInputType* output, PixelInputType* value)
{
	int i;
	int size = sizeof(PixelInputType) / sizeof(float);
	float *outputArray, *valueArray;
	outputArray = output;
	valueArray = value;
	for (i = 0;i < size;i++)
		outputArray[i] = valueArray[i];
}


void processPoint(PixelInputType* input, int x, int y, float z, ShaderParams* params, __global ShaderGlobal* sg)
{
	int ind, result;
	m3dVector4 color;
	//int ind;

	// check screen
	if (x < sg->left || x > sg->right || y < sg->bottom || y > sg->top)
		return;

	x += sg->right;
	y = sg->top - y;
	ind = sg->screenWidth*y + x; // ind in buffer


								 // check depth buffer
	if (!checkDepth(ind, 1/z, sg))
		return;


	// proccess shader
	result = PixelShader(input, params, &color);
	if (!result)
		return;

	// draw pixel
	draw(ind, z, &color, sg);
}
void rasterizer1(PixelInputType* input, ShaderParams* params, __global ShaderGlobal* sg)
{
	// there are only one point so we can only draw it immidietly
	processPoint(input, input->position.x, input->position.y, input->position.z, params, sg);
}
void rasterizer2(PixelInputType* input1, PixelInputType* input2, ShaderParams* params, __global ShaderGlobal* sg)
{
	m3dVector3 *pos1, *pos2, *pos;
	PixelInputType stepInput;
	PixelInputType nextInput;
	float slope;
	int steps;
	int x, y, i;
	pos1 = input1;
	pos2 = input2;
	slope = (pos2->y - pos1->y) / (pos2->x - pos1->x);
	// if line closer to horizontal
	if (slope > -1 && slope < 1)
	{
		// go from left to right
		if (pos1->x > pos2->x)
		{
			swap(&input2, &input1);
			swap(&pos2, &pos1);
		}
		steps = pos2->x - pos1->x + 1;
	}
	// if line closer to vertical
	else
	{
		// go from bottom to up
		if (pos1->y > pos2->y)
		{
			swap(&input2, &input1);
			swap(&pos2, &pos1);
		}
		steps = pos2->y - pos1->y + 1;
	}
	copyPI(&nextInput, input1);
	createDeltaPI(&stepInput, input1, input2, steps);
	for (i = 0;i < steps;i++)
	{
		pos = &nextInput;
		processPoint(&nextInput, pos->x, pos->y, pos->z, params, sg);
		addPI(&nextInput, &nextInput, &stepInput);
	}
}
void rasterizer3(PixelInputType* input1, PixelInputType* input2, PixelInputType* input3, ShaderParams* params, __global ShaderGlobal* sg)
{
	PixelInputType stepInput1, stepInput2, stepInput3;
	PixelInputType nextInputL, nextInputR;
	int steps, steps1, steps2, i;

	rgb color;
	int j;

	// order verticies py1<py2<py3
	if (input2->position.y < input1->position.y)
	{
		swap(&input2, &input1);
	}
	if (input3->position.y < input1->position.y)
	{
		swap(&input3, &input1);
	}
	if (input3->position.y < input2->position.y)
	{
		swap(&input3, &input2);
	}

	steps = input3->position.y - input1->position.y + 1;
	createDeltaPI(&stepInput1, input1, input3, steps);
	createDeltaPI(&stepInput2, input1, input2, (input3->position.y - input1->position.y) / steps*(input2->position.y - input1->position.y));
	createDeltaPI(&stepInput3, input2, input3, (input3->position.y - input1->position.y) / steps*(input3->position.y - input2->position.y));
	copyPI(&nextInputL, input1);
	copyPI(&nextInputR, input1);
	stepInput2.position.y = stepInput3.position.y = stepInput1.position.y;

	// bottom side
	while (nextInputL.position.y <= input2->position.y)
	{
		nextInputR.position.y = nextInputL.position.y;
		rasterizer2(&nextInputL, &nextInputR, params, sg);
		addPI(&nextInputL, &nextInputL, &stepInput1);
		addPI(&nextInputR, &nextInputR, &stepInput2);
	}
	// up side
	copyPI(&nextInputL, input3);
	copyPI(&nextInputR, input3);
	//return;
	while (nextInputL.position.y > input2->position.y)
	{
		nextInputR.position.y = nextInputL.position.y;
		rasterizer2(&nextInputL, &nextInputR, params, sg);
		subPI(&nextInputL, &nextInputL, &stepInput1);
		subPI(&nextInputR, &nextInputR, &stepInput3);
	}
}
