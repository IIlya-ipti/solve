#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<algorithm>
#include<iomanip>
#include<map>
#include <cmath>
using namespace std;

struct Point {
	int value;
	int heap = 0;
	int  repeat = 0;
	Point* left = NULL;
	Point* right = NULL;
};
vector<Point*> nu;
class Tree {
public:
	Point* head = NULL;

	vector<int> Add(int& num) {
		int right = 0;
		int left = 0;
		Point *value = new Point;
		value->value = num;
		if (head == NULL) { head = value; return{ right,left,0 };
		}
		else {
			Point* new_number = head; 
			nu = {};
			while (1) {
				if (new_number->value > value->value) {
					right += (new_number->repeat + 1);
					if(new_number->right != NULL){ right += new_number->right->heap + new_number->right->repeat + 1; }
					new_number->heap++; 
					if (new_number->left == NULL) {
						new_number->left = value;    allprove(nu); nu = {}; return{ left,right,0 };
					}
					new_number = new_number->left; 
				}
				else if (new_number->value < value->value) { 
					left += (new_number->repeat + 1);;
					if (new_number->left != NULL) { left += new_number->left->heap + new_number->left->repeat + 1; }
					new_number->heap++; 
					if (new_number->right == NULL) { new_number->right = value;  allprove(nu); nu = {}; return{ left,right,0 }; }
					new_number = new_number->right;
				}
				else {
					new_number->repeat++;
					if (new_number->left != NULL) { left += new_number->left->heap + new_number->left->repeat + 1;}
					if (new_number->right != NULL) { right += new_number->right->heap + new_number->right->repeat + 1; }
					nu = {};
					delete value;
					return{left,right,new_number->repeat };

				}
				nu.push_back(new_number);
			}
		}
	}
	void allprove(vector<Point *> x) {
		for (int i = x.size() - 1; i >= 0; i--) {
			int pr = Proverka(x[i]);
			if (pr == 1) { rideleft(x[i]); }
			else if (pr == 2) { rideright(x[i]); }
		}
	}
	int Proverka(Point* x) {
		if (x->left == NULL && x->right == NULL) { return 0; }
		if (x->right != NULL && x->left != NULL ) {
			if (x->right->heap - x->left->heap > 1) { return 1; }
			if (x->left->heap - x->right->heap > 1) { return 2; }
			return 0;
		}
		if (x->right == NULL && x->left->heap > 1) { return 2; }
		if (x->left == NULL && x->right->heap > 1) { return 1; }
		return 0;
	}
	void add(Point* x) {
		x->heap = 0;
		if (x->left != NULL) {
			x->heap += x->left->heap + x->left->repeat + 1;
		}
		if (x->right != NULL) {
			x->heap += x->right->heap + x->right->repeat + 1;
		}
	}
	void rideright(Point* x) {
		Point* b = new Point;
		*b = *x;
		Point* c = x->left;
		*x = *(x->left);
		Point* a = x->right;
		x->right = b;
		x->right->left = a;
		x->heap = x->right->heap + x->right->repeat - x->repeat;
		add(x->right);
		a = new Point;
		b = new Point;
		delete a;
		delete b;
		delete c;
	}
	void rideleft(Point* x) {
		Point* b = new Point;
		*b = *x;
		Point* c = x->right;
		*x = *(x->right);
		Point* a = x->left;
		x->left = b;
		x->left->right = a;
		x->heap = x->left->heap + x->left->repeat - x->repeat;
		add(x->left);
		a = new Point;
		b = new Point;
		delete a;
		delete b;
		delete c;
	}
};
int solve() {
	int n;
	cin >> n;
	vector<int> sums(n);
	for (int i = 0; i < n; i++) {
		cin >> sums[i];
	}
	Tree numbers;
	vector<int> nums1, nums2;
	for (int i = 0; i < n; i++) {
		nums2 = numbers.Add(sums[i]);
		if (i > 0 && (i - nums2[0] -(i - 1 -  nums1[0]) + nums1[2] < 0 ||  i - nums2[1] -(i - 1 - nums1[1]) + nums1[2] < 0) )
		{
			cout << "NO" << endl; return 0;
		}
		nums1 = nums2;
	}
	cout << "YES" << endl;
	return 0;
}
int main() {
	int t;
	cin >> t;
	for (int j = 0; j < t; j++) {
		solve();
	}
	return 0;
}