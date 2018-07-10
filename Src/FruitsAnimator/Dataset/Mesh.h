#ifndef _FRUITS_ANIMATOR_MESH_H_
#define _FRUITS_ANIMATOR_MESH_H_

#include <Fruits2D/Fruits2D.h>

namespace FRUITS_ANIMATOR
{
	typedef F2D::DelaunayTriangulation DT;

	struct MeshNode : public Object, public ISerializable
	{
		f2Vec2 texCoords, projCoords;

		MeshNode();
		MeshNode(const MeshNode& node);
		MeshNode(const f2Vec2& pos, float hWidth, float hHeight);
		MeshNode& operator = (const MeshNode& node);

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		void initCoords(const f2Vec2& pos, float hWidth, float hHeight);
	};

	class MeshNodeCmp
	{
	public:
		bool operator () (const MeshNode* lhs, const MeshNode* rhs) const {
			return lhs->projCoords.x < rhs->projCoords.x 
				|| lhs->projCoords.x == rhs->projCoords.x && lhs->projCoords.y < rhs->projCoords.y;
		}
	}; // MeshNodeCmp

	class MeshTri : public IObject
	{
	public:
		MeshTri();
		MeshTri(const MeshTri& tri);
		~MeshTri();

		//
		// IObject interface
		//
		virtual MeshTri* clone();

		void getNodes(std::vector<MeshNode*>& nodes);

	private:
		MeshNode* m_nodes[3];

		friend class Mesh;
		friend class MorphingSprite;

	}; // MeshTri

	class Mesh : public IObject, public ISerializable
	{
	public:
		Mesh(float width, float height);
		Mesh(const Mesh& mesh);
		~Mesh();

		//
		// IObject interface
		//
		virtual Mesh* clone();

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		void insertNode(const f2Vec2& pos);
		void deleteNode(const f2Vec2& pos);
		const std::vector<MeshTri*>& getAllTris() const;

		bool isMerged() const;
		void mergeNodes();
		void separateNodes();

		void tween(const Mesh& start, const Mesh& end, float process);

		void clear();

	private:
		void loadTrisFromDT();

	private:
		std::vector<MeshTri*> m_tris;

		DT* m_dt;

		float m_halfWidth, m_halfHeight;

		bool m_isMerged;

	}; // Mesh
}

#endif // _FRUITS_ANIMATOR_MESH_H_