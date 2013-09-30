#ifndef POST_EFFECT_HPP
#define POST_EFFECT_HPP

class PostEffect
{
public:
  virtual           ~PostEffect();

  virtual void      apply(const sf::RenderTexture& input, sf::RenderTarget& output) = 0;
  static bool       isSupported();

protected:
  static void       applyShader(const sf::Shader& shader, sf::RenderTarget& output);
};

#endif // POST_EFFECT_HPP
