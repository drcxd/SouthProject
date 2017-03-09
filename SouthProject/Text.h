#ifndef __Text__
#define __Text__

#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

class Text
{
public:

	~Text();

	static Text* Instance(void)
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Text();
		}

		return s_pInstance;
	}

	void setContent(const std::string &content, unsigned i);
	void draw(void);
	void drawBackground(void);
	void clean(void);
	SDL_Texture *getTextTexture(const std::string &text);

private:

	Text(void);

	std::string m_Content;
	std::vector<SDL_Texture *> m_pTextures;
	SDL_Texture *m_pBackground;

	bool setTexture(std::string content);

	TTF_Font *m_pFont;
	SDL_Color m_textColor = { 0, 0, 0 };

	std::vector<int> m_Widths;
	std::vector<int> m_Heights;

	
	static Text *s_pInstance;
};

typedef Text TheTextManager;
#endif // !__Text__
