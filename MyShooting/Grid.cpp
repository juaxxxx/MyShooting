#include "pch.h"
#include "Grid.h"
#include "UObject.h"

void Grid::Update()
{
	// 업데이트 된 셀 목록 옮기기
	UpdateCells();

	for (int x = 0; x < ROW_NUM_CELL; x++)
	{
		for (int y = 0; y < COL_NUM_CELL; y++)
		{
			for (auto iter : _cells[x][y])
			{
				HandleCell(iter);
			}
		}
	}
}

void Grid::Add(UObject* object)
{
	_updatecells[object->_gridX][object->_gridY].insert(object);
}

void Grid::DestroyCell(UObject* object)
{
	int32 x = object->_gridX;
	int32 y = object->_gridY;

	_updatecells[x][y].erase(object);
}

void Grid::Move(UObject* object)
{
	int32 x = object->_gridX;
	int32 y = object->_gridY;
	int32 px = object->_gridpreX;
	int32 py = object->_gridpreY;

	if (x < 0 || y < 0 || x > ROW_NUM_CELL - 1 || y > COL_NUM_CELL - 1) return;
	if (px < 0 || py < 0 || px > ROW_NUM_CELL - 1 || py > COL_NUM_CELL - 1) return;

	if (x == px && y == py)
		return;

	_updatecells[px][py].erase(object);
	_updatecells[x][y].insert(object);
}

void Grid::Render(HDC hdc)
{
	// 펜 생성
	HPEN myPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(hdc, myPen);


	for (int x = 0; x < ROW_NUM_CELL; x++)
	{
		// 라인 그리기
		MoveToEx(hdc, x * Grid::CELL_SIZE, 0, nullptr);
		LineTo(hdc, x * Grid::CELL_SIZE, 800);
	}

	for (int y = 0; y < COL_NUM_CELL; y++)
	{
		// 라인 그리기
		MoveToEx(hdc, 0, y * Grid::CELL_SIZE, nullptr);
		LineTo(hdc, 450, y * Grid::CELL_SIZE);
	}


	// 이전 펜 복원 및 새 펜 삭제
	SelectObject(hdc, oldPen);
	DeleteObject(myPen);
}

void Grid::UpdateCells()
{
	for (int x = 0; x < ROW_NUM_CELL; x++)
	{
		for (int y = 0; y < COL_NUM_CELL; y++)
		{
			_cells[x][y] = _updatecells[x][y];
		}
	}
}

void Grid::HandleCell(UObject* object)
{
	int32 x = object->_gridX;
	int32 y = object->_gridY;

	if (x < 0 || y < 0 || x > ROW_NUM_CELL - 1 || y > COL_NUM_CELL - 1) return;

	for (auto cell : _cells[x][y])
	{
		if (object->GetActive() && cell->GetActive())
			object->OnColliderEnter(cell);
	}
	if (x > 0 && y > 0)
	{
		for (auto cell : _cells[x - 1][y - 1])
		{
			if (object->GetActive() && cell->GetActive())
				object->OnColliderEnter(cell);
		}
	}
	if (x > 0)
	{
		for (auto cell : _cells[x - 1][y])
		{
			if (object->GetActive() && cell->GetActive())
				object->OnColliderEnter(cell);
		}
	}
	if (x < ROW_NUM_CELL - 1 && y > 0)
	{
		for (auto cell : _cells[x + 1][y - 1])
		{
			if (object->GetActive() && cell->GetActive())
				object->OnColliderEnter(cell);
		}
	}
	if (y > 0)
	{
		for (auto cell : _cells[x][y - 1])
		{
			if (object->GetActive() && cell->GetActive())
				object->OnColliderEnter(cell);
		}
	}
	if (x < ROW_NUM_CELL - 1)
	{
		for (auto cell : _cells[x + 1][y])
		{
			if (object->GetActive() && cell->GetActive())
				object->OnColliderEnter(cell);
		}
	}
}
