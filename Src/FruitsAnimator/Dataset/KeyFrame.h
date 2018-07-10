#ifndef _FRUITS_ANIMATOR_KEY_FRAME_H_
#define _FRUITS_ANIMATOR_KEY_FRAME_H_

#include <Fruits2D/Fruits2D.h>

namespace FRUITS_ANIMATOR
{
	class Sprite;
	class LibraryPanel;

	class KeyFrame
	{
	public:
		KeyFrame(int time);
		~KeyFrame();

		void loadFromTextFile(std::ifstream& fin, const LibraryPanel& library);
		void storeToTextFile(std::ofstream& fout, const LibraryPanel& library) const;

		bool isEmpty() const;

		void insertSprite(Sprite* sprite);
		bool removeSprite(f2Sprite* sprite);
		const std::vector<Sprite*>& getAllSprites() const;

		bool hasClassicTween() const;
		void setClassicTween(bool has = true);

		int getTime() const;

	private:
		void clear();

	private:
		int m_time;

		std::vector<Sprite*> m_sprites;

		bool m_bClassicTween;

	}; // KeyFrame
}

#endif // _FRUITS_ANIMATOR_KEY_FRAME_H_