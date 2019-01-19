#pragma once
#include <stdio.h>
#include <list>
#include <Windows.h>

class SnakeNode {
private:
	COORD current_pos;
	COORD last_pos;
public:
	SnakeNode() :current_pos({ 0,0 }), last_pos({ 0,0 }) {};
	SnakeNode(int x, int y) :current_pos({ (SHORT)x,(SHORT)y }), last_pos({ (SHORT)x,(SHORT)y }) {};
	SnakeNode(const SnakeNode& s) {
		current_pos = s.current_pos;
		last_pos = s.last_pos;
	}
	
	void updatePos(int x, int y) {
		last_pos = current_pos;
		current_pos = { (SHORT)x,(SHORT)y };
	}
	void updatePos(const COORD pos) {
		last_pos = current_pos;
		current_pos = pos;
	}
	const COORD& lastPos()const { return last_pos; }
	const COORD& pos() const { return current_pos; }

	bool operator==(const SnakeNode& node)const {
		return ((node.pos().X == pos().X) && (node.pos().Y == pos().Y));
	}
};

class Snake {
private:
	std::list<SnakeNode> body;
	COORD current_pos;
	COORD last_pos;
public:
	enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

	Snake() :current_pos({ 0,0 }), last_pos({ 0,0 }) {
		SnakeNode head;
		body.push_back(head);
		this->dir = STOP;
	}
	Snake(const int& x, const int& y) :current_pos({ (SHORT)x,(SHORT)y }), last_pos({ (SHORT)x,(SHORT)y }) {
		SnakeNode head(x, y);
		body.push_back(head);
		this->dir = STOP;
	}

	void addNode() {
		SnakeNode new_chain(tail());
		body.push_back(new_chain);
	}

	void updateHeadPos(const int& x,const int& y) {
		last_pos = current_pos;
		current_pos = { (SHORT)x,(SHORT)y };
		head().updatePos(x, y);
	}
	void updateHeadPos(const COORD& pos) {
		updateHeadPos(pos.X, pos.Y);
	}
	
	const COORD& lastHeadPos() { return last_pos; }
	const COORD& headPos() { return current_pos; }

	bool collisionCheck(const int& x, const int& y) {
		return (current_pos.X == (SHORT)x && current_pos.Y == (SHORT)y);
	}
	bool collisionCheck(const COORD& pos) {
		return collisionCheck(pos.X, pos.Y);
	}
	
	bool collisionOnWidth(const int& left, const int& right) {
		return (current_pos.X <= (SHORT)left || current_pos.X >= (SHORT)right);
	}
	bool collisionOnHeight(const int& down, const int& up) {
		return (current_pos.Y <= (SHORT)down || current_pos.Y >= (SHORT)up);
	}
	
	SnakeNode tail() {
		return body.back();
	}
	SnakeNode& head() {
		
		return *(body.begin());
	}

	std::list<SnakeNode> getBody() {
		return body;

	}


	void move() {
		//Updating the snake nodes's location:
		bool firstNode = true;
		auto tmp = body.begin();
		for (auto i = ++body.begin(); i != body.end(); ++i) {
			if (firstNode) {
				firstNode = false;
				i->updatePos(tmp->pos());
				++tmp;
				continue;
			}
			i->updatePos(tmp->lastPos());
			++tmp;
		}

		//Updating the Head location:
		switch (this->dir) {
		case LEFT:
			updateHeadPos(headPos().X - 1, headPos().Y);
			break;
		case RIGHT:
			updateHeadPos(headPos().X + 1, headPos().Y);
			break;
		case UP:
			updateHeadPos(headPos().X, headPos().Y - 1);
			Sleep(50);
			break;
		case DOWN:
			updateHeadPos(headPos().X, headPos().Y + 1);
			Sleep(50);
			break;
		default:
			break;
		}



	}

	void changeDirection(const eDirection& new_dir) {

		switch (new_dir)
		{
		case UP: 
			if (this->dir != DOWN)
				this->dir = UP;
			break;
		case DOWN: 
			if (this->dir != UP)
				this->dir = DOWN;
			break;
		case RIGHT: 
			if (this->dir != LEFT)
				this->dir = RIGHT;
			break;
		case LEFT:
			if (this->dir != RIGHT)
				this->dir = LEFT;
			break;
		default:
			this->dir = STOP;
			break;
		}
	}

	void reset() {

		this->dir = STOP;
		if (body.size() <= 1) return;
		for(size_t i = 0; i < body.size(); i++){
			body.pop_back();
		}

	}

private:
	eDirection dir;
};