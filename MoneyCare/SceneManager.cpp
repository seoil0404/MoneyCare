#include "Scene.h"
#include "Coroutine.h"
#include "DebugLog.h"

SceneType SceneManager::scene = SceneType::Budget;

AddScene* SceneManager::addScene;
ViewScene* SceneManager::viewScene;
CategoryScene* SceneManager::categoryScene;
BudgetScene* SceneManager::budgetScene;

void SceneManager::Initialize()
{
	addScene = new AddScene();
	viewScene = new ViewScene();
	categoryScene = new CategoryScene();
	budgetScene = new BudgetScene();
}

void SceneManager::UpdateScene()
{
	ClearScene(SceneType::Add);
	ClearScene(SceneType::View);
	ClearScene(SceneType::Category);
	ClearScene(SceneType::Budget);
	Initialize();
	IncludeScene(scene);
}

void SceneManager::MoveScene(SceneType _scene)
{
	if (scene != _scene)
	{
		ClearScene(scene);
		IncludeScene(_scene);
		scene = _scene;
	}
}

void SceneManager::ClearScene(SceneType _scene)
{
	switch (_scene)
	{
	case SceneType::Add:
		addScene->Translate(sf::Vector2f(-1600, 0), 5);
		break;
	case SceneType::View:
		break;
	case SceneType::Category:
		categoryScene->Translate(sf::Vector2f(-1600, 0), 5);
		break;
	case SceneType::Budget:
		break;
	default:
		break;
	}
}

void SceneManager::IncludeScene(SceneType _scene)
{
	switch (_scene)
	{
	case SceneType::Add:
		addScene->setScroll();
		addScene->Translate(sf::Vector2f(3200, 0), 100);
		Coroutine::AddCoroutine([&]() { addScene->Translate(sf::Vector2f(-1600, 0), 5);});
		break;
	case SceneType::View:
		break;
	case SceneType::Category:
		categoryScene->setScroll();
		categoryScene->Translate(sf::Vector2f(3200, 0), 100);
		Coroutine::AddCoroutine([&]() { categoryScene->Translate(sf::Vector2f(-1600, 0), 5);});
		break;
	case SceneType::Budget:
		break;
	default:
		break;
	}
}

Scene::~Scene() {};