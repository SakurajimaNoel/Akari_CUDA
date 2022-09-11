#include "Akari.h"
constexpr char CHANNEL_NUM = 3;

int main()
{
	const int image_width = 256;
	const int image_height = 256;

	//uint8_t* image_data = new uint8_t[image_width * image_height * CHANNEL_NUM];
	auto image_data = std::make_unique<uint8_t[]>(image_width * image_height * CHANNEL_NUM);
	uint32_t index = 0;

	for (int j = image_height - 1; j >= 0; --j)
	{
		//std::cerr << "\rScanlines Remaining: " << j <<  " " << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			auto r = double(i) / (image_width - 1);
			auto g = double(j) / (image_height - 1);
			auto b = 0.25;

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			image_data[index++] = ir;
			image_data[index++] = ig;
			image_data[index++] = ib;
		}
	}
	stbi_write_png("image.png", image_width, image_height, CHANNEL_NUM, image_data.get(), image_width * CHANNEL_NUM);
	image_data.reset();
	return 0;
}