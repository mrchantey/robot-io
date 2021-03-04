#pragma once

class Module
{

public:


	//PICK BACK UP HERE
	int childIndex;
	Module *parent;

	bool enabled = true;

	void Update() {
		if (enabled)
			OnUpdate();
	}

	void PublishLong(long val) {
		parent->BeginPublish(childIndex);
		parent->ContinuePublishLong(val);
	}

	void PublishDouble(double val) {
		parent->BeginPublish(childIndex);
		parent->ContinuePublishLong(val);
	}

	virtual	void BeginPublish(int myChildIndex) {
		parent->BeginPublish(childIndex);
		parent->ContinuePublishLong(myChildIndex);
	}

	virtual void ContinuePublishLong(long val) {
		parent->ContinuePublishLong(val);
	}
	virtual void ContinuePublishDouble(double val) {
		parent->ContinuePublishDouble(val);
	}

	virtual int ParseValues(char **values, int index) {
		return index;
	};

	void SetEnabled(bool val) {
		enabled = val;
		if (val == true)
			OnEnable();
		else
			OnDisable();
	}

	virtual void OnCallbacksAttached() {}

protected:
	virtual void OnEnable() {}
	virtual void OnDisable() {}
	virtual void OnUpdate() {}
};