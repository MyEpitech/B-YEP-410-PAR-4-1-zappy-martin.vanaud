/*
** EPITECH PROJECT, 2022
** project
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include <utility>

    #include "AThreeDimensionObject.hpp"

namespace Object {

    /**
     * @brief Player class
     */
    class Player : public AThreeDimensionObject {
        public:
            /**
             * @brief Construct a new Player object
             *
             * @param pathToRessources pair of path to ressources texture and model
             * @param pathToAnimation path to ressource animation
             * @param nbAnimation number of animation
             * @param position 3 dimensional Position
             * @param type map object type
             */
            Player(std::pair<std::string, std::string> const &pathToRessources, std::string const pathToAnimation, unsigned int nbAnimation, Position const &position, Object::MAP_OBJECTS type);
            /**
             * @brief Construct a new Player object
             *
             * @param pathToModel path to ressource model
             * @param pathToRessources path to ressource texture
             * @param pathToAnimation path to ressource animation
             * @param numberOfAnimations number of animation
             * @param position 3 dimensional Position
             * @param type map object type
             */
            Player(Object::Render::MyModel &pathToModel, Object::Render::MyTexture &pathToRessources, Object::Render::MyAnimation &pathToAnimation, unsigned int numberOfAnimations, Position const &position, Object::MAP_OBJECTS type);
            /**
             * @brief Destroy the Player object
             */
            ~Player() override;

            void draw() override;
            /**
             * @brief Player Animation
             *
             * @param animNb number of animation
             */
            void animation(std::size_t animNb);
            /**
             * @brief Move player
             *
             * @param position player position
             * @param direction new player position
             */
            void move(Position const &position, Position const &direction);

            /**
             * @brief Set life player
             */
            void die() { _isAlive = false; };
            /**
             * @brief Check if player is dead
             *
             * @return true
             * @return false
             */
            bool isAlive() { return _isAlive; };

            /**
             * @brief Get player speed
             *
             * @return float
             */
            float getSpeed() const { return _speed; };
            /**
             * @brief Set player speed
             *
             * @param addSpeed add speed
             */
            void setSpeed(bool addSpeed);

            /**
             * @brief Get if player is moving
             *
             * @return true
             * @return false
             */
            bool getIsMoving() const { return _isMoving; };
            /**
             * @brief Set is moving player value
             *
             * @param isMoving bool isMoving value
             */
            void setIsMoving(bool isMoving);

        private:

            std::pair<float, float> _defaultSpeed = {0.5f, 0.8f};

            float _speed;

            float _scale;
            int _life;
            bool _isAlive = true;
            bool _isMoving = false; ///< is moving
    };
}

#endif /* !PLAYER_HPP_ */