

void spliter2D1(PixelInputType* psInput, ShaderParams* params, __global ShaderGlobal* sg)
{
	// There can be 2D splitters
	// ...
	// ...

	rasterizer1(psInput, params, sg);
}
void spliter2D2(PixelInputType* psInput1, PixelInputType* psInput2, ShaderParams* params, __global ShaderGlobal* sg)
{
	// There can be 2D splitters
	// ...
	// ...
	rasterizer2(psInput1, psInput2, params, sg);
}
void spliter2D3(PixelInputType* psInput1, PixelInputType* psInput2, PixelInputType* psInput3, ShaderParams* params, __global ShaderGlobal* sg)
{
	// There can be 2D splitters
	// ...
	// ...
	rasterizer3(psInput1, psInput2, psInput3, params, sg);
}


void spliter1(PixelInputType* psInput, ShaderParams* params, __global ShaderGlobal* sg)
{
	m3dVector3* position = psInput; // first value is position

									// Finish if point out of z planes
	if (position->z <  0 || position->z >  sg->farZ)
		return;

	// split in 2D and go next
	spliter2D1(psInput, params, sg);
}
void spliter2(PixelInputType* psInput1, PixelInputType* psInput2, ShaderParams* params, __global ShaderGlobal* sg)
{
	m3dVector3 *pos1, *pos2;
	pos1 = psInput1; // first value is position
	pos2 = psInput2;

	// Finish if both points out of near Z
	if (pos1->z <  0 && pos2->z < 0)
		return;

	// Separate line if it cross near Z plane
	if (pos1->z <0 || pos2->z < 0)
	{
		float cutPercent;
		// swap so P1 is out of plane
		if (pos2->z < 0)
		{
			swap(&psInput1, &psInput2);
			swap(&pos1, &pos2);
		}
		cutPercent = -pos1->z / (pos2->z - pos1->z);
		interpolatePI(psInput1, psInput1, psInput2, cutPercent);
	}

	// split in 2D and go next
	spliter2D2(psInput1, psInput2, params, sg);
}
void spliter3(PixelInputType* psInput1, PixelInputType* psInput2, PixelInputType* psInput3, ShaderParams* params, __global ShaderGlobal* sg)
{
	int result;
	m3dVector3 *pos1, *pos2, *pos3;
	pos1 = psInput1; // first value is position
	pos2 = psInput2;
	pos3 = psInput3;

	// Finish if all points out of near Z
	if (pos1->z < 0 && pos2->z < 0 && pos3->z < 0)
		return;

	// Separate bottom part of triangle if it cross near Z plane
	// if two points out of plane
	if ((pos1->z < 0 && pos2->z < 0) ||
		(pos1->z < 0 && pos3->z < 0) ||
		(pos2->z < 0 && pos3->z < 0))
	{
		float cutPercent1, cutPercent2;
		// swap so P1 is in plane
		if (pos2->z >= 0)
		{
			swap(&psInput1, &psInput2);
			swap(&pos1, &pos2);
		}
		if (pos3->z >= 0)
		{
			swap(&psInput1, &psInput3);
			swap(&pos1, &pos3);
		}

		cutPercent1 = -pos2->z / (pos1->z - pos2->z);
		cutPercent2 = -pos3->z / (pos1->z - pos3->z);
		interpolatePI(psInput2, psInput2, psInput1, cutPercent1);
		interpolatePI(psInput3, psInput3, psInput1, cutPercent2);
	}
	// only one point out of plane
	else if (pos1->z < 0 || pos2->z < 0 || pos3->z < 0)
	{
		PixelInputType psInput4;
		float cutPercent1, cutPercent2;

		// swap so P1 is out of plane
		if (pos2->z < 0)
		{
			swap(&psInput1, &psInput2);
			swap(&pos1, &pos2);
		}
		if (pos3->z < 0)
		{
			swap(&psInput1, &psInput3);
			swap(&pos1, &pos3);
		}

		cutPercent1 = -pos1->z / (pos2->z - pos1->z);
		cutPercent2 = -pos1->z / (pos2->z - pos1->z);
		interpolatePI(&psInput4, psInput1, psInput3, cutPercent2);
		interpolatePI(psInput1, psInput1, psInput2, cutPercent1);
		spliter2D3(psInput2, psInput3, &psInput4, params, sg);
	}

	// split in 2D and go next
	spliter2D3(psInput1, psInput2, psInput3, params, sg);
}

