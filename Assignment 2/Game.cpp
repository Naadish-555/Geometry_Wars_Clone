#include "Game.h"
#include<fstream>
#include<iostream>

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path)
{
	//TODO : read in config file here
	// use the premade playerconfig, enemyconfig, bulletconfig variables

	//set up default window parameters
	m_window.create(sf::VideoMode(1280, 720), "Shapez Warz");
	m_window.setFramerateLimit(60);

	spawnPlayer();

}

void Game::run()
{
	//TODO : add pause functionality in here
	//	some systems function while pause (rendering)
	//	some systems shouldn't (movement/input)
	m_running = true;
	while (m_running)
	{
		m_entities.update();

		if (!m_paused)  //showed as an example for m_paused may or may not be final implementation
		{
			sEnemySpawner();
			sMovement();
			sCollision();
			sUserInput();
		}

		sRender();
		m_currentFrame++;
		//increment the current frame
		//may need to be moved when pause implemented
	}
}

void Game::setPaused(bool paused)
{
	//TODO
}

void Game::sMovement()
{
	//TODO : implement all entity movement in this function
	// you should read the m_player->cInput component to determine if the player is moving
	m_player->cTransform->velocity = Vec2(0, 0);


	if (m_player->cInput->up)
	{
		m_player->cTransform->velocity.y = -5.0f;
	}
	if (m_player->cInput->left)
	{
		m_player->cTransform->velocity.x = -5.0f;
	}
	if (m_player->cInput->down)
	{
		m_player->cTransform->velocity.y = 5.0f;
	}
	if (m_player->cInput->right)
	{
		m_player->cTransform->velocity.x = 5.0f;
	}

	//Sample movement speed update
	m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
	m_player->cTransform->pos.y += m_player->cTransform->velocity.y;

	for (auto bullets : m_entities.getEntities("Bullet"))
	{
		bullets->cTransform->pos += bullets->cTransform->velocity;
	}
}

void Game::sUserInput()
{
	//TODO : handle user input here

	//note that you should only be setting the player's input component variables here
	// you should not implement the player's movement logic here
	// the movement system will read the variables you set in this function

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		//this event triggers when the window is closed
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}

		//this event is triggered when a key is pressed 
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				std::cout << "W key pressed\n";
				m_player->cInput->up = true;
				break;
			case sf::Keyboard::A:
				std::cout << "A key pressed\n";
				m_player->cInput->left = true;
				break;
			case sf::Keyboard::S:
				std::cout << "S key pressed\n";
				m_player->cInput->down = true;
				break;
			case sf::Keyboard::D:
				std::cout << "D key pressed\n";
				m_player->cInput->right = true;
				break;
			default: break;
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				std::cout << "W key released\n";
				m_player->cInput->up = false;
				break;
			case sf::Keyboard::A:
				std::cout << "A key released\n";
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::S:
				std::cout << "S key released\n";
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::D:
				std::cout << "D key released\n";
				m_player->cInput->right = false;
				break;
			default: break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << "Left mouse button clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
				spawnBullet(m_player,Vec2(event.mouseButton.x,event.mouseButton.y));
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "Right mouse button clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
				//call special weapon here
			}
		}
	}
}

void Game::sLifespan()
{
	//TODO: implement all lifespan functionality
	//if entity has > 0 remaining lifespan , subtract 1
	// if it has lifespan and is alive
	//		scale its alpha channel properly
	// if it has lifespan and its time is up
	//		destroy the entity
}

void Game::sRender()
{
	//TODO : changfe the code below to draw all of the entities
	//	sample drawing of the player entity that we have created
	m_window.clear();

	//set the position of the shape based on the entity's transform->pos
	//m_player->cShape->circle.setPosition(m_player->cTransform->pos.x, m_player->cTransform->pos.y);

	//set the rotation of the shaped based on the entity's transform->angle
	//m_player->cTransform->angle += 1.0f;
	//m_player->cShape->circle.setRotation(m_player->cTransform->angle);

	//draw the entity's sf::circleShape
	//m_window.draw(m_player->cShape->circle);

	//what will be actually implemented , mentioned in the video 
	for (auto e : m_entities.getEntities())
	{
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
		e->cTransform->angle += 1.0f * e->cShape->circle.getPointCount();
		e->cShape->circle.setRotation(e->cTransform->angle);
		m_window.draw(e->cShape->circle);
	}

	m_window.display();
}

void Game::sEnemySpawner()
{
	//TODO : code which implements enemy spawning should go here
	if (m_currentFrame - m_lastEnemySpawnTime > 60)
	{
		spawnEnemy();
	}
	//		use(m_currentFrame - m_lastEnemySpawnTime) to determine
	//		how long it has been since the last enemy spawned
	
}

void Game::sCollision()
{
	//TODO: implement all proper collisiion between entities
	// be sure to use th ecollisioin radius , not the shape radius
}

void Game::spawnPlayer()
{
	//Note: all of the below code is just sample code to show creation of entity with this system, we have to use configuration.txt file for passing all the attributes of players, enemies and other entities
	//TODO : finish adding all properties of the player with the correct values from the config

	//we create every entity by calling EntityManager.addEntity(tag)
	//This returns a std::shared_ptr<Entity>, so we use 'auto' to save typing
	auto entity = m_entities.addEntity("Player");

	//Give this entity a Transform so it spawns at (200,200) with velocity (1,1) and angle 0
	float mx = m_window.getSize().x / 2.0f;
	float my = m_window.getSize().y / 2.0f; 
	//for spawning in the middle of screen logic

	entity->cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(.0f, .0f), 0.0f);

	//The entity shape will have radius 32, 8 sides, dark grey fill and red oultine of thickness 4
	entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);

	//Add an input component to the player so that we can use inputs
	entity->cInput = std::make_shared<CInput>();

	//Since we want this entity to be our player , set our Game's player variable to be this Entity
	// This goes slightly againt the EntityManager paradigm, but we use the player so much that it's worth it
	m_player = entity;
}

//spawn an enemy at random position
void Game::spawnEnemy()
{
	//TODO : make sure the enemy is spawned properly with the m_enemyConfig variables
	//the enemy must be spawned completely within the bounds of the window
	//view the video for some hints related to logic of spawning within the bounds
	//auto e = m_entityManager.addEntity(args);
	auto enemy = m_entities.addEntity("Enemy");
	enemy->cShape = std::make_shared<CShape>(32, 3 + (rand() % (1 + 8 - 3)), sf::Color(255, 255, 0), sf::Color(255, 255, 255), 2);
	float r = enemy->cShape->circle.getRadius();
	float mx = r + (rand() % (size_t) (1 + (m_window.getSize().x-r) - r));
	float my = r + (rand() % (size_t) (1 + (m_window.getSize().y-r) - r));
	enemy->cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(0, 0), 0);
	//record when the most recent enemy was spawned
	m_lastEnemySpawnTime = m_currentFrame;
}

//spawns the small enemies when a big one (input entity e ) explodes
void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
	//TODO : spawns small enemies at the location of the input enemy e 

	//when we create the smaller enemy , we have to read the values of the original enemy
	// - spawn a number of small enemies equal to the vertices of the original enemy 
	// - set each small enemy to the same color as the original, half the size
	// - small enemies are worth double points or the original enemy
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& target)
{
	//TODO: implement the spawning of a bullet which travels towards target
	// - bullet speed is given as a scalar speed
	// - you must set the velocity by using formula in notes
	auto bullet = m_entities.addEntity("Bullet");
	bullet->cShape = std::make_shared<CShape>(10, 20, sf::Color(255, 255, 255), sf::Color(255, 255, 255), 2);
	bullet->cTransform = std::make_shared<CTransform>(entity->cTransform->pos, (target - entity->cTransform->pos).normalize() * 20, 0.0f);
	
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
	//TODO : implement your own special weapon
}


