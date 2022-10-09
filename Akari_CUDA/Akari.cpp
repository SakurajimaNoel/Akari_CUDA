#include "Akari.h"
constexpr char CHANNEL_NUM = 3;

int main()
{
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);


	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto btm_lft_crnr = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);



	
	
	auto image_data = std::make_unique<uint8_t[]>(image_width * image_height * CHANNEL_NUM);
	uint32_t index = 0;

	for (int j = image_height - 1; j >= 0; --j)
	{
		//std::cerr << "\rScanlines Remaining: " << j <<  " " << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			auto u = double(i) / (image_width - 1);
			auto v = double(j) / (image_height - 1);
			ray r(origin, btm_lft_crnr +  horizontal * u +  vertical * v - origin);
			color pixel_color = ray_color(r);
			//color pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
			
			image_data[index++] = color_value(pixel_color.x);
			image_data[index++] = color_value(pixel_color.y);
			image_data[index++] = color_value(pixel_color.z);
		}
	}
	stbi_write_png("image.png", image_width, image_height, CHANNEL_NUM, image_data.get(), image_width * CHANNEL_NUM);
	image_data.reset();
	return 0;
}