

int PixelShader(PixelInputType* input, ShaderParams* params, m3dVector4* outputColor)
{
	*outputColor = params->color;

	return 1;
}
