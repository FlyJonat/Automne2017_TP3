#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\queue\stack.h"

//Laurent Ricard - 1562287
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace queueTest
{
	TEST_CLASS(StackTest)
	{
	public:
		Stack<double>* queue;
		Stack<double>* queue2;

		TEST_METHOD(StackTestSize)
		{
			queue = new Stack<double>();
			queue->push(5);
			queue->push(9);
			queue->push(-4);
			Assert::IsTrue(queue->size() == 3);
			queue->push(5);
			queue->push(9);
			queue->push(-4);
			queue->push(5);
			queue->push(9);
			Assert::IsTrue(queue->size() == 8);
			queue->pop();
			queue->pop();
			queue->pop();
			queue->pop();
			Assert::IsTrue(queue->size() == 4);
		}

		TEST_METHOD(StackTestFront)
		{
			queue = new Stack<double>();
			queue->push(5);
			queue->push(9);
			queue->push(-4);

			Assert::IsTrue(queue->front() == -4);
			Assert::IsFalse(queue->front() == 9);
			Assert::IsFalse(queue->front() == 5);
		}

		TEST_METHOD(StackTestFrontAvecPop)
		{
			queue = new Stack<double>();
			queue->push(5);
			queue->push(9);
			queue->push(-4);

			Assert::IsTrue(queue->front() == -4);
			Assert::IsFalse(queue->front() == 5);
			Assert::IsFalse(queue->front() == 9);

			queue->pop();
			Assert::IsTrue(queue->front() == 9);
			queue->pop();
			Assert::IsTrue(queue->front() == 5);
			queue->pop();
			queue->push(3);
			Assert::IsTrue(queue->front() == 3);
		}

		TEST_METHOD(StackTestBack)
		{
			queue = new Stack<double>();
			queue->push(5);
			queue->push(9);
			queue->push(-4);

			Assert::IsTrue(queue->back() == 5);
			Assert::IsFalse(queue->back() == 9);
			Assert::IsFalse(queue->back() == -4);
		}
		TEST_METHOD(StackTestBackAvecPop)
		{
			queue = new Stack<double>();
			queue->push(5);
			queue->push(9);
			queue->push(-4);

			Assert::IsTrue(queue->back() == 5);
			Assert::IsFalse(queue->back() == -4);
			Assert::IsFalse(queue->back() == 9);

			queue->pop();
			Assert::IsTrue(queue->back() == 5);
			queue->pop();
			Assert::IsTrue(queue->back() == 5);
			queue->pop();
			queue->push(3);
			Assert::IsTrue(queue->back() == 3);
		}
		TEST_METHOD(StackTestEmpty)
		{
			queue = new Stack<double>();
			Assert::IsTrue(queue->empty());
			queue->push(5);
			Assert::IsFalse(queue->empty());
			queue->push(9);
			queue->push(-4);
			Assert::IsFalse(queue->empty());

			queue->pop();
			Assert::IsFalse(queue->empty());
			queue->pop();
			Assert::IsFalse(queue->empty());
			queue->pop();
			Assert::IsTrue(queue->empty());
		}
		TEST_METHOD(StackTestSwap)
		{
			queue = new Stack<double>();
			queue2 = new Stack<double>();

			queue->push(5);
			queue->push(9);
			queue->push(-4);

			queue2->push(3);
			queue2->push(-17);
			queue2->push(-2);
			queue2->push(12);
			queue2->push(28);

			queue->swap(*queue2);

			Assert::IsTrue(queue->size() == 5);
			Assert::IsTrue(queue->front() == 28);
			Assert::IsTrue(queue->back() == 3);
			queue->pop();

			Assert::IsTrue(queue->front() == 12);
			Assert::IsTrue(queue->back() == 3);
			queue->pop();

			Assert::IsTrue(queue->front() == -2);
			Assert::IsTrue(queue->back() == 3);
			queue->pop();

			Assert::IsTrue(queue->front() == -17);
			Assert::IsTrue(queue->back() == 3);
			queue->pop();

			Assert::IsTrue(queue->front() == 3);
			Assert::IsTrue(queue->back() == 3);


			Assert::IsTrue(queue2->size() == 3);
			Assert::IsTrue(queue2->front() == -4);
			Assert::IsTrue(queue2->back() == 5);
			queue2->pop();

			Assert::IsTrue(queue2->front() == 9);
			Assert::IsTrue(queue2->back() == 5);
			queue2->pop();

			Assert::IsTrue(queue2->front() == 5);
			Assert::IsTrue(queue2->back() == 5);
		}
	};
}