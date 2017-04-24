#pragma once

template <class T>
class Node
{
public:
	Node<T>(T &data)
	{
		mpNext = nullptr;
		mpPrev = nullptr;
		setData(data);
	}

	~Node<T>()
	{
		if (getNext() != nullptr)
			delete mpNext;

		setNext(nullptr);
	}

	Node<T> *getPrev() const { return mpPrev; }
	Node<T> *getNext() const { return mpNext; }
	T &getData() { return mData; }

	void setData(const T &data) { mData = data; }
	void setNext(Node<T> *next) { mpNext = next; }
	void setPrev(Node<T> *prev) { mpPrev = prev; }

private:
	T mData;
	Node<T> *mpNext,
			*mpPrev;
};

template <class T>
class Node<T*>
{
public:
	Node<T*>(T *&data)
	{
		mpNext = nullptr;
		mpPrev = nullptr;
		setData(data);
	}

	~Node<T*>()
	{
		if (getData() != nullptr)
			delete mData;
		if (getNext() != nullptr)
			delete mpNext;

		setNext(nullptr);
	}

	Node<T*> *getPrev() const { return mpPrev; }
	Node<T*> *getNext() const { return mpNext; }
	T *&getData() { return mData; }

	void setData(T *&data) { mData = data; }
	void setNext(Node<T*> *next) { mpNext = next; }
	void setPrev(Node<T*> *prev) { mpPrev = prev; }

private:
	T* mData;
	Node<T*> *mpNext,
			*mpPrev;
};

