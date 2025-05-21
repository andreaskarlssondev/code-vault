#include "LooseQuadTree.h"

#include <DebugDrawer.h>


LooseQuadTreeNode::~LooseQuadTreeNode()
{
	for (auto child : myChildren)
	{
		delete child;
	}
}

bool LooseQuadTreeNode::contains(Vector2f aPosition)
{
	Vector2f min = { myPosition.x - myHalfWidth, myPosition.y - myHalfWidth };
	Vector2f max = { myPosition.x + myHalfWidth, myPosition.y + myHalfWidth };

	return aPosition.x >= min.x && aPosition.y >= min.y && aPosition.x <= max.x && aPosition.y <= max.y;
}

bool LooseQuadTreeNode::Insert(QuadTreeObject& aObject)
{
	if (!Inside(aObject))
	{
		return false;
	}

	if (!myChildren.empty())
	{
		LooseQuadTreeNode* closestChild = FindClosestChild(this, aObject);
		if (closestChild->Insert(aObject))
		{
			return true;
		}
	}

	myObjects.push_back(&aObject);

	if (!myDivided && myObjects.size() > myCapacity)
	{
		CreateChildren();
	}

	return true;
}

bool LooseQuadTreeNode::Inside(QuadTreeObject& aObject)
{
	bool insideX = abs(aObject.position.x - myPosition.x) < (GetHalfSize() - aObject.halfWidth);
	bool insideY = abs(aObject.position.y - myPosition.y) < (GetHalfSize() - aObject.halfWidth);

	return insideX && insideY;
}

LooseQuadTreeNode* LooseQuadTreeNode::FindClosestChild(LooseQuadTreeNode* aNode, QuadTreeObject& aObject)
{
	LooseQuadTreeNode* closest = nullptr;
	float minSqrDistance = FLT_MAX;

	for (auto child : aNode->GetChildren())
	{
		float sqrDistance = (child->GetPosition() - aObject.position).LengthSqr();
		if (sqrDistance < minSqrDistance)
		{
			closest = child;
			minSqrDistance = sqrDistance;
		}
	}

	return closest;
}

void LooseQuadTreeNode::CreateChildren()
{
	float halfWidthChildren = myHalfWidth * 0.5f;

	for (int i = 0; i < 4; ++i)
	{
		LooseQuadTreeNode* node = new LooseQuadTreeNode;
		node->myHalfWidth = halfWidthChildren;
		node->myLoosenessfactor = myLoosenessfactor;
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

void LooseQuadTree::Init(const float aWidth, const float aHeight, const float aLossenessfactor)
{
	myWidth = aWidth;
	myHeight = aHeight;	

	myRoot.myHalfWidth = myWidth * 0.5f;
	myRoot.myPosition.x = myRoot.myHalfWidth;
	myRoot.myPosition.y = myRoot.myHalfWidth;
	myRoot.myLoosenessfactor = aLossenessfactor;
}


void LooseQuadTree::GetIntersected(Vector2f aPosition, std::vector<LooseQuadTreeNode*>& outIntersected)
{
	if (myRoot.contains(aPosition))
	{
		outIntersected.push_back(&myRoot);
		SearchIntersected(&myRoot, aPosition, outIntersected);
	}
}

void LooseQuadTree::SearchIntersected(LooseQuadTreeNode* aNode, Vector2f& aPosition, std::vector<LooseQuadTreeNode*>& outIntersected)
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

void LooseQuadTree::Render(DebugDrawer& aDebugDrawer, LooseQuadTreeNode& aNode)
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

