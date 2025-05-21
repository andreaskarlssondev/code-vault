#pragma once

#include "QuadTreeObject.h"

#include <Math/Vector2.h>

#include <vector>

class DebugDrawer;
class LooseQuadTree;

class LooseQuadTreeNode
{
	friend class LooseQuadTree;

	public:
		LooseQuadTreeNode() = default;
		~LooseQuadTreeNode();

		inline const std::vector<LooseQuadTreeNode*>& GetChildren() const { return myChildren; }
		inline std::vector<QuadTreeObject*> GetObjects() { return myObjects; }

		inline const Vector2f& GetPosition() const { return myPosition; }
		inline float GetSize() const { return GetHalfSize() * 2.f; }
		inline float GetLooseness() const { return myLoosenessfactor; }

		bool contains(Vector2f aPosition);

	private:
		const float GetHalfSize() const { return myHalfWidth * myLoosenessfactor; }
		
		bool Insert(QuadTreeObject& aObject);
		bool Inside(QuadTreeObject& aObject);

		LooseQuadTreeNode* FindClosestChild(LooseQuadTreeNode* aNode, QuadTreeObject& aObject);

		void CreateChildren();

	private:
		Vector2f myPosition;
		float myHalfWidth;
		float myLoosenessfactor;

		bool myDivided;
		static const int myCapacity = 4;

		std::vector<LooseQuadTreeNode*> myChildren;
		std::vector<QuadTreeObject*> myObjects;
};


class LooseQuadTree
{

	public:
		LooseQuadTree() = default;
		~LooseQuadTree() = default;

		void Init(const float aWidth, const float aHeight, const float aLossenessfactor = 1.f);

		void Render(DebugDrawer& aDebugDrawer)
		{
			Render(aDebugDrawer, myRoot);
		}

		void Insert(QuadTreeObject& aObject)
		{
			myRoot.Insert(aObject);
		}

		void GetIntersected(Vector2f aPosition, std::vector<LooseQuadTreeNode*>& outIntersected);

	private:

		void Render(DebugDrawer& aDebugDrawer, LooseQuadTreeNode& aNode);

		void SearchIntersected(LooseQuadTreeNode* aNode, Vector2f& aPosition, std::vector<LooseQuadTreeNode*>& outIntersected);

	private:
		float myWidth;
		float myHeight;

		LooseQuadTreeNode myRoot;
};