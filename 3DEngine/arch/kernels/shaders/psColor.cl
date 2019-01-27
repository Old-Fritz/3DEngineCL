

int PixelShader(PixelInputType* input, ShaderParams* params, m3dVector4* outputColor)
{
	*outputColor = input->color;

	return 1;
}
