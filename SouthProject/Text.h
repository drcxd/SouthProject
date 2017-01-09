#ifndef __Text__
#define __Text__

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
#include <vector>

class Text
{
public:

	~Text();

	static Text* Instance(void)
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new Text();
		}

		return s_pInstance;
	}

	void setContent(std::string, unsigned i);
	void draw(void);
	void drawBackground(void);
	void clean(void);
	SDL_Texture *getTextTexture(std::string text);

private:

	std::string m_content;
	std::vector<SDL_Texture *> m_pTextures;
	SDL_Texture *m_pBackground;

	bool setTexture(std::string content);
	TTF_Font *m_pFont;
	SDL_Color m_textColor = { 0, 0, 0 };

	std::vector<int> m_Widths;
	std::vector<int> m_Heights;

	Text(void);
	static Text *s_pInstance;
};

typedef Text TheTextManager;
#endif // !__Text__
