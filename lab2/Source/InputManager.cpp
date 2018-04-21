#include "InputManager.h"

void InputManager::HandleKeyPressed(int key)
{
	auto iter = mKeyToActionMap.find(key);
	if (iter != mKeyToActionMap.end()) {
		ActionMappingPtr ptr = iter->second;
		if (ptr->mPressedDelegate != nullptr) {
			ptr->mPressedDelegate->Execute();
		}
	}

	auto iter2 = mKeyToAxisMap.find(key);
	if (iter2 != mKeyToAxisMap.end()) {
		AxisMappingPtr ptr = iter2->second;
		if (key == ptr->mPositiveKey) {
			ptr->mValue += 1.0f;
			ptr->mDelegate->Execute(ptr->mValue);
		}
		if (key == ptr->mNegativeKey) {
			ptr->mValue -= 1.0f;
			ptr->mDelegate->Execute(ptr->mValue);
		}
	}
}

void InputManager::HandleKeyReleased(int key)
{
	auto iter = mKeyToActionMap.find(key);
	if (iter != mKeyToActionMap.end()) {
		ActionMappingPtr ptr = iter->second;
		if (ptr->mReleasedDelegate != nullptr) {
			ptr->mReleasedDelegate->Execute();
		}
	}

	auto iter2 = mKeyToAxisMap.find(key);
	if (iter2 != mKeyToAxisMap.end()) {
		AxisMappingPtr ptr = iter2->second;
		if (key == ptr->mPositiveKey) {
			ptr->mValue -= 1.0f;
			ptr->mDelegate->Execute(ptr->mValue);
		}
		if (key == ptr->mNegativeKey) {
			ptr->mValue += 1.0f;
			ptr->mDelegate->Execute(ptr->mValue);
		}
	}
}

void InputManager::AddActionMapping(const std::string& name, int key)
{
	ActionMappingPtr ptr = std::make_shared<ActionMapping>();
	ptr->mName = name;
	ptr->mKey = key;
	mNameToActionMap.emplace(name, ptr);
	mKeyToActionMap.emplace(key, ptr);
}

void InputManager::AddAxisMapping(const std::string& name, int positiveKey, int negativeKey)
{
	AxisMappingPtr ptr = std::make_shared<AxisMapping>();
	ptr->mName = name;
	ptr->mPositiveKey = positiveKey;
	ptr->mNegativeKey = negativeKey;
	mNameToAxisMap.emplace(name, ptr);
	mKeyToAxisMap.emplace(positiveKey, ptr);
	mKeyToAxisMap.emplace(negativeKey, ptr);
}

void InputManager::BindActionInternal(const std::string& name, InputEvent event, ActionDelegatePtr delegate)
{
	auto iter = mNameToActionMap.find(name);
	if (iter != mNameToActionMap.end()) { 
		ActionMappingPtr ptr = iter->second;
		if (event == IE_Pressed) {
			ptr->mPressedDelegate = delegate;
		}
		if (event == IE_Released) {
			ptr->mReleasedDelegate = delegate;
		}
	}
}

void InputManager::BindAxisInternal(const std::string& name, AxisDelegatePtr delegate)
{
	auto iter = mNameToAxisMap.find(name);
	if (iter != mNameToAxisMap.end()) {
		AxisMappingPtr ptr = iter->second;
		ptr->mDelegate = delegate;
	}
}