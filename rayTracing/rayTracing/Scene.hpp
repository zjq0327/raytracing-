#pragma once

#include"Light.hpp"
#include"Camera.hpp"

class Scene
{
public:
	int width = 1280;
	int height = 960;
	Camera camera;

	Vector3f backgroundColor = Vector3f(0.235294, 0.67451, 0.843137);
	int maxDepth = 100;

	Scene()
	{}

	void Add(std::shared_ptr<Object> object) { objects.push_back(std::move(object)); }
	void Add(std::shared_ptr<Light> light) { lights.push_back(std::move(light)); }

	const std::vector<std::shared_ptr<Object> >& get_objects() const { return objects; }
	const std::vector<std::shared_ptr<Light> >& get_lights() const { return lights; }

private:
	vector<shared_ptr<Object>> objects;
	std::vector<std::shared_ptr<Light> > lights;

};