#ifndef _ANIM_SET_HPP_
#define _ANIM_SET_HPP_

class AnimSet {
public:
    std::string name;
    std::vector<Animation> animations;

    AnimSet(); // creates an empty animation set
    AnimSet(const std::string &filepath, std::vector<sf::Texture*> animTextures, const std::string &name); // tries to load an animation set file from the specified path
    ~AnimSet();
};

#endif // _ANIM_SET_HPP_
