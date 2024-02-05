#include"Renderer.hpp"
#include"Sphere.hpp"
#include <memory>

int main()
{

	Scene scene;

	shared_ptr<Sphere> s1 = make_shared<Sphere>(Vector3f(0, 0, 1), 0.5);

	shared_ptr<Light> l1 = make_shared<Light>(Vector3f(1, 1, -1), Vector3f(1, 1, 1));

	scene.Add(std::move(s1));
	scene.Add(std::move(l1));

	Renderer r;
	r.Render(scene);

	return 0;
}

