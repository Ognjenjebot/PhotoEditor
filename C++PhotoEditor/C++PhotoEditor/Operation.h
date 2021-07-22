#ifndef OPERATION
#define OPERATION
#include"Image.h"
#include<set>
#include<map>
#include<math.h>
#include<algorithm>
#include<vector>
#include<iterator>
#include<string>


using namespace std;

class Image;

class Operation {
public:
	virtual void execute(Image &i) = 0;
};

class BasicOperation1 : public Operation {
public:
	void execute(Image &i) override;
};

class BasicOperation2 : public Operation {
public:
	void execute(Image &i) override;
};

class BasicOperation3 : public Operation {
public:
	void execute(Image &i) override;
};

class BasicOperation4 : public Operation {
public:
	void execute(Image &i) override;
};

class BasicOperation5 : public Operation {
public:
	void execute(Image &i) override;
};

class BasicOperation6 : public Operation {
public:
	void execute(Image &i) override;
};

class BasicOperation7 : public Operation {
public:
	void execute(Image &i) override;
};

class BasicOperation8 : public Operation {
public:
	void execute(Image &i) override;
};

class BasicOperation9 : public Operation {
public:
	void execute(Image &i) override;
};

class BasicOperation10 : public Operation {
public:
	void execute(Image &i) override;
};

class BasicOperation11 : public Operation {
public:
	void execute(Image &i) override;
};

class InverseOperation : public Operation {
public:
	void execute(Image &i) override;
};

class BlackWhiteOperation : public Operation {
public:
	void execute(Image &i) override;
};

class GreyShadesOperation : public Operation {
public:
	void execute(Image &i) override;
};

class MedianaOperation : public Operation {
public:
	void execute(Image &i) override;
};


class CompositeOperation : public Operation {
	vector<Operation *> operations;
	std::string name;
public:
	void addOperation(Operation *op);

	void execute(Image &i) override;
};

#endif