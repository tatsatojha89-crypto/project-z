
#include<SFML/Graphics.hpp>

int main()
{

	std::srand(static_cast<unsigned int>(std::time(nullptr)));


	//making of space ship sprite
	sf::Texture texture;
	if (!texture.loadFromFile("../../../assets/spaceShip.png"))
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
	if (!flameTexture.loadFromFile("../../../assets/flame1.png"))
	{
		return -1;
	}
	sf::Sprite flame(flameTexture);
	flame.setOrigin(flameTexture.getSize().x / 2.f,flameTexture.getSize().y / 4.f);
	

     

	//making of bullet sprite
	sf::Texture bulletTexture;
	if (!bulletTexture.loadFromFile("../../../assets/attack8.png"))
	{
		return -1;
	}
	sf::Sprite bullet(bulletTexture);
	bullet.setOrigin(bulletTexture.getSize().x/2, bulletTexture.getSize().y/5);
	bullet.setScale( 0.3f, 0.3f);
	sf::Vector2f velocity(0.f, -600.f); // Bullet velocity

	bool bulletActive = false; 



	//making window
    sf::RenderWindow window(sf::VideoMode(800, 600),"SFML Template");
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
			bullet.setPosition(sprite.getPosition().x, sprite.getPosition().y );
			bulletActive = true;
		}
		if (bulletActive) {
			bullet.move(velocity * dt);
			if (bullet.getPosition().y < -200) {
				bulletActive = false;
			}
		}


		// ----- Flame Logic -----

		sf::Vector2f shipPos = sprite.getPosition();

		// Get the ship's actual scaled height
		float shipHeight =sprite.getLocalBounds().height * sprite.getScale().y;

		// Distance from ship center to its bottom
		float offsetY = shipHeight / 2.f;

		// Small adjustment so flame connects to ship
		offsetY += 5.f;

		// shift flame
		float offsetX = -currentTilt* 0.8f;

		// Put flame at bottom of ship
		flame.setPosition(shipPos.x + offsetX-1.f,shipPos.y + offsetY);

		// Flame tilts with the ship
		flame.setRotation(currentTilt);

		// Flickering flame
		float flicker =0.8f + static_cast<float>(rand() % 40) / 100.f;

		// Scale flame
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
			flame.setScale(0.03f * flicker*1.2f, 0.03f * flicker*1.2f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
			flame.setScale(0.03f * flicker * 0.8f, 0.03f * flicker * 0.8f);

		}
		else
		flame.setScale(0.03f * flicker,0.03f * flicker);

		// Flame color variation
		int green = 120 + rand() % 80;

		flame.setColor(sf::Color(255, green, 0, 200));

		// ----- Drawing -----

		window.clear();
		

		 
		if (bulletActive) {
			window.draw(bullet);
		}
		window.draw(sprite);
		window.draw(flame);
		window.display();
	}
    return 0;
}