#include"Renderer.hpp"
#include "Ray.hpp"



// 开始支持光线弹射了
Vector3f castRay(const Ray& ray, const Scene& scene)
{
	const std::vector<std::shared_ptr<Object>>& objects = scene.get_objects();

	float minTnear = kInfinity;
	hit_record record;
	bool isTrace = false;
	for (const auto& e : objects)
	{
		float tnear;
		if (e->hit(ray,tnear, record) == true)
		{
			isTrace = true;
			if (tnear < minTnear)
			{
				tnear = minTnear;
				record.hit_obj = e;
			}
		}
	}
	
	// 增加光照
	if (isTrace == true)
	{
		const std::vector<std::shared_ptr<Light>>& lights = scene.get_lights();
		Vector3f color = 0;

		// Phong
		for (const auto& light : lights)
		{
			Vector3f n = record.normal;

			Vector3f lightDir = light->position - record.point;
			float lightDistance2 = dotProduct(lightDir, lightDir);
			lightDir = normalize(lightDir);

			float LdotN = std::max(0.f, dotProduct(lightDir, n));

			Vector3f lightAmt = light->intensity * LdotN;
			Vector3f reflectionDirection = reflect(-lightDir, n);

			Vector3f specularColor = powf(std::max(0.f, -dotProduct(reflectionDirection, ray.direction())),
				record.hit_obj->specularExponent) * light->intensity;

			color += lightAmt * record.hit_obj->evalDiffuseColor() * record.hit_obj->Kd + specularColor * record.hit_obj->Ks;
		}

		return color;
	}


	return scene.backgroundColor;
}


void Renderer::Render(const Scene& scene)
{
	std::vector<Vector3f> framebuffer(scene.width * scene.height);

	const Camera& camera = scene.camera;
	const Vector3f& center = camera.eyePos;
	float imageAspectRatio = scene.width / (float)scene.height;

	float focal_length = (camera.eyePos - camera.lookAt).length();
	float theta = deg2rad(scene.camera.vfov);
	float h = tan(theta / 2);
	float viewport_height = 2 * h * focal_length;
	float viewport_width = viewport_height * imageAspectRatio;

	// Calculate the u,v,w unit basis vectors for the camera coordinate frame.
	Vector3f w = normalize(camera.eyePos - camera.lookAt);
	Vector3f u = normalize(crossProduct(camera.lookUp, w));
	Vector3f v = crossProduct(w, u);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	Vector3f viewport_u =  viewport_width * u;
	Vector3f viewport_v = -viewport_height * v;

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	Vector3f pixel_delta_u = viewport_u / scene.width;
	Vector3f pixel_delta_v = viewport_v / scene.height;

	// Calculate the location of the upper left pixel.
	Vector3f viewport_upper_left = center
		- (focal_length* w) - viewport_u / 2 - viewport_v / 2;
	Vector3f pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	int curbuf = 0;
	// 打入光线
	for (int j = 0; j < scene.height; j++)
	{
		for (int i = 0; i < scene.width; i++)
		{
			Vector3f pixelCenter = pixel00_loc + pixel_delta_u * i + pixel_delta_v * j;
			Vector3f direction = normalize(pixelCenter - center);
			Ray r(center, direction);
			framebuffer[curbuf++] = castRay(r, scene);
		}
	}

	// 写入文件中
	printImage(scene, framebuffer);
}