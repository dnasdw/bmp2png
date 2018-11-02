#include <sdw.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

int UMain(int argc, UChar* argv[])
{
	if (argc != 3)
	{
		return 1;
	}
	FILE* fp = UFopen(argv[1], USTR("rb"), false);
	if (fp == nullptr)
	{
		return 1;
	}
	u32 uPngWidth = 0;
	u32 uPngHeight = 0;
	n32 nPngChannel = 0;
	u8* pData = stbi_load_from_file(fp, reinterpret_cast<n32*>(&uPngWidth), reinterpret_cast<n32*>(&uPngHeight), &nPngChannel, 4);
	fclose(fp);
	if (pData == nullptr)
	{
		return 1;
	}
	fp = UFopen(argv[2], USTR("wb"), false);
	if (fp == nullptr)
	{
		stbi_image_free(pData);
		return 1;
	}
	n32 nResult = stbi_write_png_to_func(stbi__stdio_write, fp, uPngWidth, uPngHeight, 4, pData, uPngWidth * 4);
	fclose(fp);
	stbi_image_free(pData);
	return nResult != 0 ? 0 : 1;
}
