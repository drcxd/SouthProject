#ifndef __Text__
#define __Text__

#include <SDL.h>
#include <string>
#include <SDL_ttf.h>

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

	void setContent(std::string);
	void draw(void);
	void drawBackground(void);
	void clean(void);
	SDL_Texture *getTextTexture(std::string text);

private:

	std::string m_content;
	SDL_Texture *m_pTexture;
	SDL_Texture *m_pBackground;

	bool setTexture(std::string content);
	TTF_Font *m_pFont;
	SDL_Color m_textColor = { 0, 0, 0 };

	int m_Width;
	int m_Height;

	Text(void);
	static Text *s_pInstance;
};

typedef Text TheTextManager;
#endif // !__Text__
