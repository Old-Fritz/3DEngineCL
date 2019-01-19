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


void processPoint(PixelInputType* input, int x, int y, float z, ShaderParams* params)
{
	int ind, result;
	float z;
	m3dVector4 color;
	ind = sg->screenWidth*y + x; // ind in buffer

								 // check screen
	if (x < sg->left || x>  sg->right || y <  sg->bottom || y> sg->top)
		return;

	// check depth buffer
	if (!checkDepth(x, y, z))
		return;

	// proccess shader
	result = PixelShader(input, params, &color);
	if (!result)
		return;

	// draw pixel
	draw(ind, z, &color);
}
void rasterizer1(PixelInputType* input, ShaderParams* params)
{
	m3dVector3* position = input;
	// there are only one point so we can only draw it immidietly
	processPoint(input, position->x, position->y, position->z, params);
}
void rasterizer2(PixelInputType* input1, PixelInputType* input2, ShaderParams* params)
{
	m3dVector3 *pos1, *pos2, *pos;
	PixelInputType stepInput;
	PixelInputType nextInput;
	float slope;
	int steps;
	int x, y, i;
	pos1 = input1;
	pos2 = input2;
	slope = (pos2->x - pos1->x) / (pos2->y - pos2->y);
	// if line closer to horizontal
	if (slope > -1 && slope < 1)
	{
		// go from left to right
		if (pos1->x > pos2->x)
		{
			swap(&input2, &input1);
			swap(&pos2, &pos1);
		}
		steps = pos2->x - pos1->x;
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
		steps = pos2->y - pos1->y;
	}
	copyPI(&nextInput, input1);
	createDeltaPI(&stepInput, input1, input2, steps);
	for (i = 0;i < steps;i++)
	{
		pos = &nextInput;
		processPoint(&nextInput, pos->x, pos->y, pos->z, params);
		addPI(&nextInput, &nextInput, &stepInput);
	}
}
void rasterizer3(PixelInputType* input1, PixelInputType* input2, PixelInputType* input3, ShaderParams* params)
{
	m3dVector3 *pos1, *pos2, *pos3;
	PixelInputType stepInput1, stepInput2, stepInput3;
	PixelInputType nextInputL, nextInputR;
	int steps, i;
	// order verticies py1<py2<py3
	pos1 = input1;
	pos2 = input2;
	pos3 = input3;
	if (pos2->y < pos1->y)
	{
		swap(&input2, &input1);
		swap(&pos2, &pos1);
	}
	if (pos3->y < pos1->y)
	{
		swap(&input3, &input1);
		swap(&pos3, &pos1);
	}
	if (pos3->y < pos2->y)
	{
		swap(&input3, &input2);
		swap(&pos3, &pos2);
	}
	steps = pos3->y - pos1->y;
	createDeltaPI(&stepInput1, input1, input3, steps);
	createDeltaPI(&stepInput2, input1, input2, (pos3->y - pos1->y) / steps*(pos2->y - pos1->y));
	createDeltaPI(&stepInput3, input2, input3, (pos3->y - pos1->y) / steps*(pos3->y - pos2->y));
	copyPI(&nextInputL, &input1);
	copyPI(&nextInputR, &input1);

	// bottom side
	while (((m3dVector3*)&nextInputL)->y <= pos2->y)
	{
		rasterizer2(&nextInputL, &nextInputR, params);
		addPI(&nextInputL, &nextInputL, &stepInput1);
		addPI(&nextInputR, &nextInputR, &stepInput2);
	}
	// up side
	copyPI(&nextInputL, &input3);
	copyPI(&nextInputR, &input3);
	while (((m3dVector3*)&nextInputL)->y > pos2->y)
	{
		rasterizer2(&nextInputL, &nextInputR, params);
		subPI(&nextInputL, &nextInputL, &stepInput1);
		subPI(&nextInputR, &nextInputR, &stepInput3);
	}
}