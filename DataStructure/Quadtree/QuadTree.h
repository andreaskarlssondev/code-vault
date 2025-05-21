#pragma once

#include "QuadTreeObject.h"

#include <Math/Vector2.h>

#include <vector>


class QuadTree;

class QuadTreeNode
{
	friend class QuadTree;

	public:
		QuadTreeNode() = default;
		~QuadTreeNode();

		inline const std::vector<QuadTreeNode*>& GetChildren() const { return myChildren; }
		inline std::vector<QuadTreeObject*> GetObjects() { return myObjects; }

		bool contains(Vector2f aPosition);

	private:
		bool Insert(QuadTreeObject& aObject);
		bool Inside(QuadTreeObject& aObject);

		void CreateChildren();

	private:
		Vector2f myPosition;
		float myHalfWidth;
		bool myDivided;

		static const int myCapacity = 4;

		std::vector<QuadTreeNode*> myChildren;
		std::vector<QuadTreeObject*> myObjects;
};


class QuadTree
{

	public:
		QuadTree() = default;
		~QuadTree() = default;

		void Init(const float aWidth, const float aHeight);

		void Render(DebugDrawer& aDebugDrawer)
		{
			Render(aDebugDrawer, myRoot);
		}

		void Insert(QuadTreeObject& aObject)
		{
			myRoot.Insert(aObject);
		}

		void GetIntersected(Vector2f aPosition, std::vector<QuadTreeNode*>& outIntersected);

	private:

		void Render(DebugDrawer& aDebugDrawer, QuadTreeNode& aNode);

		void SearchIntersected(QuadTreeNode* aNode, Vector2f& aPosition, std::vector<QuadTreeNode*>& outIntersected);

	private:
		float myWidth;
		float myHeight;
		int myCapacity;

		QuadTreeNode myRoot;

};