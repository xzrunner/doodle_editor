#ifndef _FRUITS_ANIMATOR_PART_SKELETON_H_
#define _FRUITS_ANIMATOR_PART_SKELETON_H_

#include <Fruits2D/Fruits2D.h>
#include "Mesh.h"

namespace FRUITS_ANIMATOR
{
	class PartSkeleton : public IObject, public ISerializable
	{
		struct Node;
		class Joint;

	public:
		PartSkeleton(float width, float height);
		PartSkeleton(const PartSkeleton& skeleton);
		~PartSkeleton();

		//
		// IObject interface
		//
		virtual PartSkeleton* clone();

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		void pushJoint(const f2Vec2& pos);
		void popJoint();
		f2Vec2 topJoint() const;

		Joint* queryJointByPos(const f2Vec2& pos);
		Node* queryNodeByPos(const f2Vec2& pos);

		void translateJoint(Joint* joint, const f2Vec2& newPos);
		void translateNode(Node* node, const f2Vec2& newPos);
		void rotateJoint(Joint* joint, const f2Vec2& newPos);

		void onDraw() const;
		void drawMeshes() const;

		void tween(const PartSkeleton& start, const PartSkeleton& end, float process);

	private:
		void clear();

		void drawTriangle(const f2Vec2& p0, const f2Vec2& p1, const f2Vec2& p2) const;
		void drawTriangle(const f2Vec2& p0, const f2Vec2& p1, const f2Vec2& p2,
			const f2Vec2& c0, const f2Vec2& c1, const f2Vec2& c2) const;

	public:
		struct Node : public MeshNode
		{
			f2Vec2 local;	// at the coordinate system which positive x is from start joint to end joint

			Node() {}
			Node(const Node& node);

			//
			// ISerializable interface
			//
			virtual void loadFromTextFile(std::ifstream& fin);
			virtual void storeToTextFile(std::ofstream& fout) const;

		}; // Node

		class Bone;
		class Joint : public MeshNode
		{
		public:
			Joint();
			Joint(const f2Vec2& p, float hWidth, float hHeight);
			Joint(const Joint& joint);

			//
			// ISerializable interface
			//
			virtual void loadFromTextFile(std::ifstream& fin);
			virtual void storeToTextFile(std::ofstream& fout) const;

			void initNodesLocalCoords(float length);
			void initConnectedCoords(const f2Vec2& pos, float hWidth, float hHeight);

			void getNodesPos(f2Vec2& left, f2Vec2& right) const;

		private:
			Node m_left, m_right;
			Bone *m_from, *m_to;

			friend class PartSkeleton;

		}; // Joint

		class Bone : public ISerializable
		{
		public:
			Bone();
			Bone(Joint* start, Joint* end, float length, float hWidth, float hHeight);
			Bone(const Bone& bone);

			//
			// ISerializable interface
			//
			virtual void loadFromTextFile(std::ifstream& fin);
			virtual void storeToTextFile(std::ofstream& fout) const;

			float getLength() const;
			f2Vec2 getCenter() const;
			f2Vec2 getVector() const;

			void getNodesPos(f2Vec2& left, f2Vec2& right) const;

			void initNodesLocalCoords(float length);
			void initCoords(float hWidth, float hHeight, Joint* except);

		private:
			Joint *m_start, *m_end;
			Node m_left, m_right;

			friend class PartSkeleton;

		}; // Bone

	private:
		static const float JOINT_RADIUS;
		static const float NODE_RADIUS;
		static const float WIDTH_LENGTH_RATIO;

	private:
		float m_halfWidth, m_halfHeight;

		std::vector<Joint*> m_joints;

	}; // PartSkeleton
}

#endif // _FRUITS_ANIMATOR_PART_SKELETON_H_