#pragma once
#include <Common/common.h>
#include <memory>

class BaseScene;

class SceneFactory
{
public:
	static std::unique_ptr<BaseScene> CreateScene(SceneType type);
};

