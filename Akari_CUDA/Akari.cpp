#include "Akari.h"
constexpr char CHANNEL_NUM = 3;

int main()
{
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 600 ;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int sample_size = 100;
	const uint16_t depth = 50;

	auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_diffuse_sphere = std::make_shared<lambertian>(color(0.7, 0.3, 0.3));
	auto material_metal = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.3);
	hittableList world;
	world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5, material_metal));
	world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));


	camera cam;


	auto image_data = std::make_unique<uint8_t[]>(image_width * image_height * CHANNEL_NUM);




	
	for (int j = image_height - 1; j >= 0; --j)
	{
			std::cerr << "\rScanlines Remaining: " << j << " " << std::flush;

			concurrency::parallel_for(size_t(0), size_t(image_width), [&](size_t i)
			{
					color pixel_color(0, 0, 0);

					for (int s = 0; s < sample_size; ++s)
					{
						auto u = (i + random_double()) / (image_width - 1);
						auto v = (j + random_double()) / (image_height - 1);
						ray r = cam.get_ray(u, v);
						pixel_color = pixel_color + ray_color(r, world, depth);


					}

					image_data[((image_height - 1 - j) * 3 * image_width) + i + (2 * i)] = color_value(pixel_color.x, sample_size);
					image_data[((image_height - 1 - j) * 3 * image_width) + i + ((2 * i) + 1)] = color_value(pixel_color.y, sample_size);
					image_data[((image_height - 1 - j) * 3 * image_width) + i + ((2 * i) + 2)] = color_value(pixel_color.z, sample_size);



			}, Concurrency::static_partitioner());


	};

	stbi_write_png("image.png", image_width, image_height, CHANNEL_NUM, image_data.get(), image_width * CHANNEL_NUM);
	image_data.reset();
	return 0;
}