
int PixelShader(PixelInputType* input, ShaderParams* params, m3dVector4* outputColor)
{
	float lightIntensity;
	m3dVector3 color;

	lightIntensity = m3dVec3Dot(&(input->normal), &(input->lightPos));
	if (lightIntensity < 0)
		lightIntensity = -lightIntensity;
	if (lightIntensity > 1)
		lightIntensity = 1;

	if (lightIntensity > 0.0f)
	{
		m3dVec3Scale(&color, &(params->modelColor), lightIntensity*params->lightIntensity);
	}

	//m3dVec3Lerp(&color, &color, &params->modelColor, 0.8);
	
	m3dVec3Copy(outputColor, &color);

	return 1;
}
