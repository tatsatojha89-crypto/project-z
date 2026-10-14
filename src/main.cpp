
#include<SFML/Graphics.hpp>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iostream>

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int count = 0;

	//making of space ship sprite
	sf::Texture texture;
	if (!texture.loadFromFile("assets/spaceShip.png"))
	{
		return -1;
	}
	sf::Sprite sprite(texture);
	sprite.setPosition(100, 500);
	sprite.setScale(0.1f, 0.1f);
	float spaceShipSpeed = 300.0f;
	sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);

	float currentTilt = 0.f;
	float targetTilt = 0.f;
	float maxTilt = 25.f;
	float tiltSpeed = 8.f;


	//making of flame sprite
	sf::Texture flameTexture;
	if (!flameTexture.loadFromFile("assets/flame1.png"))
	{
		return -1;
	}
	sf::Sprite flame(flameTexture);
	flame.setOrigin(flameTexture.getSize().x / 2.f, flameTexture.getSize().y / 4.f);



	//making of bullet sprite
	sf::Texture bulletTexture;
	if (!bulletTexture.loadFromFile("assets/attack8.png"))
	{
		return -1;
	}
	sf::Sprite bullet(bulletTexture);
	bullet.setOrigin(bulletTexture.getSize().x / 2, bulletTexture.getSize().y / 5);
	bullet.setScale(0.3f, 0.3f);
	sf::Vector2f velocity(0.f, -700.f); // Bullet velocity
	bool bulletActive = false;


	//making smoke
	std::vector<sf::CircleShape> smokeParticles;
	std::vector<sf::Vector2f> smokeVelocity;
	std::vector<float>smokeLife;
	float smokeSpawnTimer = 0.f;
	bool smokeActive = false;


	//making of bullet2 sprite
	sf::Texture bulletTexture2;
	if (!bulletTexture2.loadFromFile("assets/flair.png"))
	{
		return -1;
	}
	sf::Sprite bullet2(bulletTexture2);
	bullet2.setOrigin(bulletTexture2.getSize().x / 2, bulletTexture2.getSize().y / 5);
	bullet2.setScale(0.3f, 0.3f);
	sf::Vector2f velocity2(0.f, -1200.f);
	bool bulletActive2 = false;
	
	

	//making window
	sf::RenderWindow window(sf::VideoMode(1200, 1000), "SFML Template");
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		float dt = clock.restart().asSeconds();
		targetTilt = 0.f; // reset target tilt each frame
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			sprite.move(-spaceShipSpeed * dt, 0);
			targetTilt = -maxTilt; // tilt left
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			sprite.move(spaceShipSpeed * dt, 0);
			targetTilt = maxTilt; // tilt right
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			sprite.move(0, -spaceShipSpeed * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			sprite.move(0, spaceShipSpeed * dt);
		}
		currentTilt += (targetTilt - currentTilt) * tiltSpeed * dt; // Smoothly interpolate towards target tilt "amazing"
		sprite.setRotation(currentTilt);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !bulletActive)
		{
			bullet.setPosition(sprite.getPosition().x, sprite.getPosition().y);
			bulletActive = true;
			smokeActive = true;
			smokeSpawnTimer = 0.f; // Reset the smoke spawn timer
		}
		if (bulletActive) {
			bullet.move(velocity * dt);
			if (bullet.getPosition().y < -200) {
				bulletActive = false;
			}
		}


		if (smokeActive)
		{
			smokeSpawnTimer += dt;

			if (smokeSpawnTimer >= 0.3f)
			{
				smokeActive = false; // Stop spawning smoke after the burst
			}
			else
			{
				for (int i = 0; i < 2; i++)
				{
					sf::CircleShape particle;

					float radius = 2.f + static_cast<float>(rand() % 6);

					particle.setRadius(radius);
					particle.setOrigin(radius, radius);

					float randomX =
						static_cast<float>((rand() % 101) - 50);

					float randomY =
						static_cast<float>((rand() % 61) - 30);

					particle.setPosition(
						sprite.getPosition().x + randomX,
						sprite.getPosition().y - 50 + randomY
					);

					particle.setFillColor(
						sf::Color(180, 180, 180, 100)
					);

					smokeParticles.push_back(particle);

					smokeVelocity.push_back(
						sf::Vector2f(static_cast<float>((rand() % 121) - 60), static_cast<float>((rand() % 121) - 60)));

					smokeLife.push_back(0.4f);
				}
			}
		}


		for (int i = smokeParticles.size() - 1; i >= 0; i--)
		{
			smokeParticles[i].move(smokeVelocity[i] * dt);

			smokeLife[i] -= dt;

			float life = smokeLife[i];

			float scale = 1.f + (0.35f - life) * 3.f;

			smokeParticles[i].setScale(scale, scale);

			sf::Uint8 alpha =
				static_cast<sf::Uint8>(255.f * (life / 0.35f));

			smokeParticles[i].setFillColor(
				sf::Color(180, 180, 180, alpha)
			);

			if (smokeLife[i] <= 0.f)
			{
				smokeParticles.erase(smokeParticles.begin() + i);
				smokeVelocity.erase(smokeVelocity.begin() + i);
				smokeLife.erase(smokeLife.begin() + i);
			}
		}



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B) && !bulletActive2) {
			bullet2.setPosition(sprite.getPosition().x, sprite.getPosition().y);
			bulletActive2 = true;
			count = 0;

		}
		

		if (bulletActive2) {
			bullet2.move(velocity2 * dt);
			
		
		if (bullet2.getPosition().y < -200) {
			bulletActive2 = false;
		}
		
		}



		// ----- Flame Logic -----

		sf::Vector2f shipPos = sprite.getPosition();

		// Get the ship's actual scaled height
		float shipHeight = sprite.getLocalBounds().height * sprite.getScale().y;

		// Distance from ship center to its bottom
		float offsetY = shipHeight / 2.f;

		// Small adjustment so flame connects to ship
		offsetY += 5.f;

		// shift flame
		float offsetX = -currentTilt * 0.8f;

		// Put flame at bottom of ship
		flame.setPosition(shipPos.x + offsetX - 1.f, shipPos.y + offsetY);

		// Flame tilts with the ship
		flame.setRotation(currentTilt);

		// Flickering logic
		float flameflicker = 0.8f + static_cast<float>(rand() % 40) / 100.f;
		float bulletFlicker = 0.93f + static_cast<float>(rand() % 50) / 100.f;
		
			
		float bulletshift = static_cast<float>(rand() % 2 - 0.5);
		bullet.setPosition(bullet.getPosition().x + bulletshift, bullet.getPosition().y);
		bullet.setScale(0.3f * bulletFlicker, 0.3f * bulletFlicker);
		bullet2.setPosition(bullet2.getPosition().x + bulletshift, bullet2.getPosition().y);
		bullet2.setScale(0.3f * bulletFlicker, 0.3f * bulletFlicker);
		
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
			flame.setScale(0.03f * flameflicker * 1.2f, 0.03f * flameflicker * 1.2f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
			flame.setScale(0.03f * flameflicker * 0.8f, 0.03f * flameflicker * 0.8f);

		}
		else
			flame.setScale(0.03f * flameflicker, 0.03f * flameflicker);
		


		// Flame color variation
		int green = 120 + rand() % 80;

		flame.setColor(sf::Color(255, green, 0, 200));





		// ----- Drawing -----

		window.clear();
		if (bulletActive) {
			window.draw(bullet);
		}
		if (bulletActive2) {
			window.draw(bullet2);
		}
		window.draw(flame);
		window.draw(sprite);
		for (auto& particle : smokeParticles)
		{
			window.draw(particle);
		}



		window.display();
		
	}
	return 0;
}