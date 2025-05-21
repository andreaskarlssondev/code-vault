#include "QuadTree.h"

QuadTreeNode::~QuadTreeNode()
{
	for (auto child : myChildren)
	{
		delete child;
	}
}

bool QuadTreeNode::contains(Vector2f aPosition)
{
	Vector2f min = { myPosition.x - myHalfWidth, myPosition.y - myHalfWidth };
	Vector2f max = { myPosition.x + myHalfWidth, myPosition.y + myHalfWidth };

	return aPosition.x >= min.x && aPosition.y >= min.y && aPosition.x <= max.x && aPosition.y <= max.y;
}

bool QuadTreeNode::Insert(QuadTreeObject& aObject)
{
	if (!Inside(aObject))
	{
		return false;
	}

	if (!myChildren.empty())
	{
		for (auto child : myChildren)
		{
			if (child->Insert(aObject))
			{
				return true;
			}
		}
	}

	myObjects.push_back(&aObject);

	if (!myDivided && myObjects.size() > myCapacity)
	{
		CreateChildren();
	}

	return true;
}

bool QuadTreeNode::Inside(QuadTreeObject& aObject)
{
	bool insideX = abs(aObject.position.x - myPosition.x) < myHalfWidth - aObject.halfWidth;
	bool insideY = abs(aObject.position.y - myPosition.y) < myHalfWidth - aObject.halfWidth;

	return insideX && insideY;
}

void QuadTreeNode::CreateChildren()
{
	float halfWidthChildren = myHalfWidth * 0.5f;

	for (int i = 0; i < 4; ++i)
	{
		QuadTreeNode* node = new QuadTreeNode;
		node->myHalfWidth = halfWidthChildren;
		myChildren.push_back(node);
	}

	myChildren[0]->myPosition = { myPosition.x - halfWidthChildren, myPosition.y + halfWidthChildren };
	myChildren[1]->myPosition = { myPosition.x + halfWidthChildren, myPosition.y + halfWidthChildren };
	myChildren[2]->myPosition = { myPosition.x + halfWidthChildren, myPosition.y - halfWidthChildren };
	myChildren[3]->myPosition = { myPosition.x - halfWidthChildren, myPosition.y - halfWidthChildren };

	myDivided = true;

	std::vector<QuadTreeObject*> objects = myObjects;
	myObjects.clear();

	for (auto object : objects)
	{
		Insert(*object);
	}
}

void QuadTree::Init(const float aWidth, const float aHeight)
{
	myWidth = aWidth;
	myHeight = aHeight;
	myCapacity = 4;

	myRoot.myHalfWidth = myWidth * 0.5f;
	myRoot.myPosition.x = myRoot.myHalfWidth;
	myRoot.myPosition.y = myRoot.myHalfWidth;
}

void QuadTree::GetIntersected(Vector2f aPosition, std::vector<QuadTreeNode*>& outIntersected)
{
	outIntersected.push_back(&myRoot);
	SearchIntersected(&myRoot, aPosition, outIntersected);
}

void QuadTree::SearchIntersected(QuadTreeNode* aNode, Vector2f& aPosition, std::vector<QuadTreeNode*>& outIntersected)
{
	for (auto child : aNode->myChildren)
	{
		if (child->contains(aPosition))
		{
			outIntersected.push_back(child);
			SearchIntersected(child, aPosition, outIntersected);
			return;
		}
	}
}

void QuadTree::Render(DebugDrawer& aDebugDrawer, QuadTreeNode& aNode)
{
	float minX = aNode.myPosition.x - aNode.myHalfWidth;
	float minY = aNode.myPosition.y - aNode.myHalfWidth;

	float maxX = aNode.myPosition.x + aNode.myHalfWidth;
	float maxY = aNode.myPosition.y + aNode.myHalfWidth;

	aDebugDrawer.DrawLine({ minX, maxY }, { maxX, maxY });
	aDebugDrawer.DrawLine({ maxX, maxY }, { maxX, minY });
	aDebugDrawer.DrawLine({ maxX, minY }, { minX, minY });
	aDebugDrawer.DrawLine({ minX, minY }, { minX, maxY });

	for (auto child : aNode.myChildren)
	{
		Render(aDebugDrawer, *child);
	}

}

