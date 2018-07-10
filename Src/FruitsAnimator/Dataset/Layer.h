#ifndef _FRUITS_ANIMATOR_LAYER_H_
#define _FRUITS_ANIMATOR_LAYER_H_

#include <Fruits2D/Fruits2D.h>

namespace FRUITS_ANIMATOR
{
	class KeyFrame;
	class Sprite;
	class LibraryPanel;

	class Layer
	{
	public:
		Layer();
		~Layer();

		void loadFromTextFile(std::ifstream& fin, const LibraryPanel& library);
		void storeToTextFile(std::ofstream& fout, const LibraryPanel& library) const;

		void insertKeyFrame(int time, KeyFrame* frame);
		bool isKeyFrame(int time) const;
		void deleteKeyFrame(int time);

		const std::string& getName() const;
		void setName(const std::string& name);
		const std::map<int, KeyFrame*>& getAllFrames() const;

		bool insertSprite(Sprite* sprite, int currFrame);
		bool removeSprite(f2Sprite* sprite);

		KeyFrame* getCurrKeyFrame(int currFrame);
		KeyFrame* getNextKeyFrame(int currFrame);

		int getFrameCount() const;

	private:
		void clear();

	private:
		std::string m_name;

		std::map<int, KeyFrame*> m_frames;

	}; // Layer
}

#endif // _FRUITS_ANIMATOR_LAYER_H_