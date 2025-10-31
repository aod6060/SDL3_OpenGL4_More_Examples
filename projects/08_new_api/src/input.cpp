#include "sys.hpp"

namespace input {

    static std::vector<InputState> keys;
    static glm::vec2 position;
    static glm::vec2 velocity;
    static std::vector<InputState> mouseButtons;

    void init() {
        keys.resize(Keyboard::KB_MAX_SIZE);

        std::for_each(keys.begin(), keys.end(), [](InputState& state) {
            state = InputState::IS_RELEASED;
        });

        position = glm::vec2(0.0f);
        velocity = glm::vec2(0.0f);

        mouseButtons.resize(MouseButtons::MB_MAX_SIZE);

        std::for_each(mouseButtons.begin(), mouseButtons.end(), [](InputState& state) {
            state = InputState::IS_RELEASED;
        });
    }

    void handleEvent(SDL_Event* e) {
        if(e->type == SDL_EVENT_KEY_DOWN) {
            if(keys[e->key.scancode] == InputState::IS_RELEASED) {
                keys[e->key.scancode] = InputState::IS_PRESSED_ONCE;
            }
        } else if(e->type == SDL_EVENT_KEY_UP) {
            if(keys[e->key.scancode] == InputState::IS_PRESSED) {
                keys[e->key.scancode] = InputState::IS_RELEASED_ONCE;
            }
        } else if(e->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if(mouseButtons[e->button.button - 1] == InputState::IS_RELEASED) {
                mouseButtons[e->button.button - 1] = InputState::IS_PRESSED_ONCE;
            }
        } else if(e->type == SDL_EVENT_MOUSE_BUTTON_UP) {
            if(mouseButtons[e->button.button - 1] == InputState::IS_PRESSED) {
                mouseButtons[e->button.button - 1] = InputState::IS_RELEASED_ONCE;
            }
        } else if(e->type == SDL_EVENT_MOUSE_MOTION) {
            position = glm::vec2(e->motion.x, e->motion.y);
            velocity = glm::vec2(e->motion.xrel, e->motion.yrel);
        }
    }

    void update() {
        std::for_each(keys.begin(), keys.end(), [](InputState& state) {
            if(state == InputState::IS_PRESSED_ONCE) {
                state = InputState::IS_PRESSED;
            }

            if(state == InputState::IS_RELEASED_ONCE) {
                state = InputState::IS_RELEASED;
            }
        });

        std::for_each(mouseButtons.begin(), mouseButtons.end(), [](InputState& state) {
            if(state == InputState::IS_PRESSED_ONCE) {
                state = InputState::IS_PRESSED;
            }

            if(state == InputState::IS_RELEASED_ONCE) {
                state = InputState::IS_RELEASED;
            }
        });

        velocity = glm::vec2(0.0f);
    }

    void release() {
        keys.clear();
        mouseButtons.clear();
    }

    bool isKeyReleased(Keyboard key) {
        return keys[key] == InputState::IS_RELEASED || keys[key] == InputState::IS_RELEASED_ONCE;
    }

    bool isKeyPressedOnce(Keyboard key) {
        return keys[key] == InputState::IS_PRESSED_ONCE;
    }

    bool isKeyPressed(Keyboard key) {
        return keys[key] == InputState::IS_PRESSED || keys[key] == InputState::IS_PRESSED_ONCE;
    }

    bool isKeyReleasedOnce(Keyboard key) {
        return keys[key] == InputState::IS_RELEASED_ONCE;    
    }

    float getKeyReleasedValue(Keyboard key) {
        return isKeyReleased(key) ? 1.0f : 0.0f;
    }

    float getKeyPressedOnceValue(Keyboard key) {
        return isKeyPressedOnce(key) ? 1.0f : 0.0f;
    }

    float getKeyPressedValue(Keyboard key) {
        return isKeyPressed(key) ? 1.0f : 0.0f;
    }

    float getKeyReleasedOnceValue(Keyboard key) {
        return isKeyReleasedOnce(key) ? 1.0f : 0.0f;
    }

    float getKeyReleasedAxis(Keyboard negative, Keyboard positive) {
        return getKeyReleasedValue(positive) - getKeyReleasedValue(negative);
    }

    float getKeyPressedOnceAxis(Keyboard negative, Keyboard positive) {
        return getKeyPressedOnceValue(positive) - getKeyPressedOnceValue(negative);
    }

    float getKeyPressedAxis(Keyboard negative, Keyboard positive) {
        return getKeyPressedValue(positive) - getKeyPressedValue(negative);
    }

    float getKeyReleasedOnceAxis(Keyboard negative, Keyboard positive) {
        return getKeyReleasedOnceValue(positive) - getKeyReleasedOnceValue(negative);
    }


    glm::vec2 toPosition() {
        return position;
    }

    glm::vec2 toVelocity() {
        return velocity;
    }

    bool isMouseButtonReleased(MouseButtons mb) {
        return mouseButtons[mb] == InputState::IS_RELEASED || mouseButtons[mb] == InputState::IS_RELEASED_ONCE;
    }

    bool isMouseButtonPressedOnce(MouseButtons mb) {
        return mouseButtons[mb] == InputState::IS_PRESSED_ONCE;
    }

    bool isMouseButtonPressed(MouseButtons mb) {
        return mouseButtons[mb] == InputState::IS_PRESSED || mouseButtons[mb] == InputState::IS_PRESSED_ONCE;
    }

    bool isMouseButtonReleasedOnce(MouseButtons mb) {
        return mouseButtons[mb] == InputState::IS_RELEASED_ONCE;
    }

    float getMouseButtonReleasedValue(MouseButtons mb) {
        return (isMouseButtonReleased(mb)) ? 1.0f : 0.0f;
    }

    float getMouseButtonPressedOnceValue(MouseButtons mb) {
        return (isMouseButtonPressedOnce(mb)) ? 1.0f : 0.0f;
    }

    float getMouseButtonPressedValue(MouseButtons mb) {
        return (isMouseButtonPressed(mb)) ? 1.0f : 0.0f;
    }

    float getMouseButtonReleasedOnceValue(MouseButtons mb) {
        return (isMouseButtonReleasedOnce(mb)) ? 1.0f : 0.0f;
    }

    float getMouseButtonReleasedAxis(MouseButtons negative, MouseButtons positive) {
        return getMouseButtonReleasedValue(positive) - getMouseButtonReleasedValue(negative);
    }

    float getMouseButtonPressedOnceAxis(MouseButtons negative, MouseButtons positive) {
        return getMouseButtonPressedOnceValue(positive) - getMouseButtonPressedOnceValue(negative);
    }

    float getMouseButtonPressedAxis(MouseButtons negative, MouseButtons positive) {
        return getMouseButtonPressedValue(positive) - getMouseButtonPressedValue(negative);
    }

    float getMouseButtonReleasedOnceAxis(MouseButtons negative, MouseButtons positive) {
        return getMouseButtonReleasedOnceValue(positive) - getMouseButtonReleasedOnceValue(negative);
    }


    bool isGrab() {
        return SDL_GetWindowRelativeMouseMode(app::getWindow());
    }

    void setGrab(bool grab) {
        SDL_SetWindowRelativeMouseMode(app::getWindow(), grab);
    }

    void toggleGrab() {
        setGrab(!isGrab());
    }



    namespace mapping {
        void createKeyboardMapping(Mapping* map, Keyboard keyboard) {
            map->isMouse = false;
            map->key = keyboard;
        }

        void createMouseButtonMapping(Mapping* map, MouseButtons mouseButton) {
            map->isMouse = true;
            map->mouseButton = mouseButton;
        }

        bool isMappingReleased(Mapping* map) {
            return (map->isMouse) ? isMouseButtonReleased(map->mouseButton) : isKeyReleased(map->key);
        }

        bool isMappingPressedOnce(Mapping* map) {
            return (map->isMouse) ? isMouseButtonPressedOnce(map->mouseButton) : isKeyPressedOnce(map->key);
        }

        bool isMappingPressed(Mapping* map) {
            return (map->isMouse) ? isMouseButtonPressed(map->mouseButton) : isKeyPressed(map->key);
        }

        bool isMappingReleasedOnce(Mapping* map) {
            return (map->isMouse) ? isMouseButtonReleasedOnce(map->mouseButton) : isKeyReleasedOnce(map->key);
        }

        float getMappingReleasedValue(Mapping* map) {
            return isMappingReleased(map) ? 1.0f : 0.0f;
        }

        float getMappingPressedOnceValue(Mapping* map) {
            return isMappingPressedOnce(map) ? 1.0f : 0.0f;
        }

        float getMappingPressedValue(Mapping* map) {
            return isMappingPressed(map) ? 1.0f : 0.0f;
        }

        float getMappingReleasedOnceValue(Mapping* map) {
            return isMappingReleasedOnce(map) ? 1.0f : 0.0f;
        }

        float getMappingReleasedAxis(Mapping* negative, Mapping* positive) {
            return getMappingReleasedValue(positive) - getMappingReleasedValue(negative);
        }

        float getMappingPressedOnceAxis(Mapping* negative, Mapping* positive) {
            return getMappingPressedOnceValue(positive) - getMappingPressedOnceValue(negative);
        }

        float getMappingPressedAxis(Mapping* negative, Mapping* positive) {
            return getMappingPressedValue(positive) - getMappingPressedValue(negative);
        }

        float getMappingReleasedOnceAxis(Mapping* negative, Mapping* positive) {
            return getMappingReleasedOnceValue(positive) - getMappingReleasedOnceValue(negative);
        }


    }

}