#pragma once

class UObject;

class Grid
{
public:
	Grid()
	{
	}

	void Update();
	void Render(HDC hdc);
	void Add(UObject* object);
	void DestroyCell(UObject* object);
	void Move(UObject* object);
	void UpdateCells();
	void HandleCell(UObject* object);

	// 800 9700
	static const uint32 ROW_NUM_CELL = 16;
	static const uint32 COL_NUM_CELL = 194;
	static const uint32 CELL_SIZE = 50;
private:
	//UObject* _cells[ROW_NUM_CELL][COL_NUM_CELL];
	set<UObject*> _cells[ROW_NUM_CELL][COL_NUM_CELL];
	set<UObject*> _updatecells[ROW_NUM_CELL][COL_NUM_CELL];
};