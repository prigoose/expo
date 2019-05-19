/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#include "ABI33_0_0Yoga.h"
#include <float.h>
#include <string.h>
#include <algorithm>
#include "ABI33_0_0Utils.h"
#include "ABI33_0_0YGNode.h"
#include "ABI33_0_0YGNodePrint.h"
#include "ABI33_0_0Yoga-internal.h"
#include "ABI33_0_0instrumentation.h"
#ifdef _MSC_VER
#include <float.h>

/* define fmaxf if < VC12 */
#if _MSC_VER < 1800
__forceinline const float fmaxf(const float a, const float b) {
  return (a > b) ? a : b;
}
#endif
#endif

using namespace facebook::ABI33_0_0yoga;

#ifdef ANDROID
static int ABI33_0_0YGAndroidLog(
    const ABI33_0_0YGConfigRef config,
    const ABI33_0_0YGNodeRef node,
    ABI33_0_0YGLogLevel level,
    const char* format,
    va_list args);
#else
static int ABI33_0_0YGDefaultLog(
    const ABI33_0_0YGConfigRef config,
    const ABI33_0_0YGNodeRef node,
    ABI33_0_0YGLogLevel level,
    const char* format,
    va_list args);
#endif

#ifdef ANDROID
#include <android/log.h>
static int ABI33_0_0YGAndroidLog(
    const ABI33_0_0YGConfigRef config,
    const ABI33_0_0YGNodeRef node,
    ABI33_0_0YGLogLevel level,
    const char* format,
    va_list args) {
  int androidLevel = ABI33_0_0YGLogLevelDebug;
  switch (level) {
    case ABI33_0_0YGLogLevelFatal:
      androidLevel = ANDROID_LOG_FATAL;
      break;
    case ABI33_0_0YGLogLevelError:
      androidLevel = ANDROID_LOG_ERROR;
      break;
    case ABI33_0_0YGLogLevelWarn:
      androidLevel = ANDROID_LOG_WARN;
      break;
    case ABI33_0_0YGLogLevelInfo:
      androidLevel = ANDROID_LOG_INFO;
      break;
    case ABI33_0_0YGLogLevelDebug:
      androidLevel = ANDROID_LOG_DEBUG;
      break;
    case ABI33_0_0YGLogLevelVerbose:
      androidLevel = ANDROID_LOG_VERBOSE;
      break;
  }
  const int result = __android_log_vprint(androidLevel, "ABI33_0_0yoga", format, args);
  return result;
}
#else
#define ABI33_0_0YG_UNUSED(x) (void) (x);

static int ABI33_0_0YGDefaultLog(
    const ABI33_0_0YGConfigRef config,
    const ABI33_0_0YGNodeRef node,
    ABI33_0_0YGLogLevel level,
    const char* format,
    va_list args) {
  ABI33_0_0YG_UNUSED(config);
  ABI33_0_0YG_UNUSED(node);
  switch (level) {
    case ABI33_0_0YGLogLevelError:
    case ABI33_0_0YGLogLevelFatal:
      return vfprintf(stderr, format, args);
    case ABI33_0_0YGLogLevelWarn:
    case ABI33_0_0YGLogLevelInfo:
    case ABI33_0_0YGLogLevelDebug:
    case ABI33_0_0YGLogLevelVerbose:
    default:
      return vprintf(format, args);
  }
}

#undef ABI33_0_0YG_UNUSED
#endif

bool ABI33_0_0YGFloatIsUndefined(const float value) {
  return facebook::ABI33_0_0yoga::isUndefined(value);
}

detail::CompactValue ABI33_0_0YGComputedEdgeValue(
    const ABI33_0_0YGStyle::Edges& edges,
    ABI33_0_0YGEdge edge,
    detail::CompactValue defaultValue) {
  if (!edges[edge].isUndefined()) {
    return edges[edge];
  }

  if ((edge == ABI33_0_0YGEdgeTop || edge == ABI33_0_0YGEdgeBottom) &&
      !edges[ABI33_0_0YGEdgeVertical].isUndefined()) {
    return edges[ABI33_0_0YGEdgeVertical];
  }

  if ((edge == ABI33_0_0YGEdgeLeft || edge == ABI33_0_0YGEdgeRight || edge == ABI33_0_0YGEdgeStart ||
       edge == ABI33_0_0YGEdgeEnd) &&
      !edges[ABI33_0_0YGEdgeHorizontal].isUndefined()) {
    return edges[ABI33_0_0YGEdgeHorizontal];
  }

  if (!edges[ABI33_0_0YGEdgeAll].isUndefined()) {
    return edges[ABI33_0_0YGEdgeAll];
  }

  if (edge == ABI33_0_0YGEdgeStart || edge == ABI33_0_0YGEdgeEnd) {
    return detail::CompactValue::ofUndefined();
  }

  return defaultValue;
}

void* ABI33_0_0YGNodeGetContext(ABI33_0_0YGNodeRef node) {
  return node->getContext();
}

void ABI33_0_0YGNodeSetContext(ABI33_0_0YGNodeRef node, void* context) {
  return node->setContext(context);
}

ABI33_0_0YGMeasureFunc ABI33_0_0YGNodeGetMeasureFunc(ABI33_0_0YGNodeRef node) {
  return node->getMeasure();
}

void ABI33_0_0YGNodeSetMeasureFunc(ABI33_0_0YGNodeRef node, ABI33_0_0YGMeasureFunc measureFunc) {
  node->setMeasureFunc(measureFunc);
}

ABI33_0_0YGBaselineFunc ABI33_0_0YGNodeGetBaselineFunc(ABI33_0_0YGNodeRef node) {
  return node->getBaseline();
}

void ABI33_0_0YGNodeSetBaselineFunc(ABI33_0_0YGNodeRef node, ABI33_0_0YGBaselineFunc baselineFunc) {
  node->setBaseLineFunc(baselineFunc);
}

ABI33_0_0YGDirtiedFunc ABI33_0_0YGNodeGetDirtiedFunc(ABI33_0_0YGNodeRef node) {
  return node->getDirtied();
}

void ABI33_0_0YGNodeSetDirtiedFunc(ABI33_0_0YGNodeRef node, ABI33_0_0YGDirtiedFunc dirtiedFunc) {
  node->setDirtiedFunc(dirtiedFunc);
}

ABI33_0_0YGPrintFunc ABI33_0_0YGNodeGetPrintFunc(ABI33_0_0YGNodeRef node) {
  return node->getPrintFunc();
}

void ABI33_0_0YGNodeSetPrintFunc(ABI33_0_0YGNodeRef node, ABI33_0_0YGPrintFunc printFunc) {
  node->setPrintFunc(printFunc);
}

bool ABI33_0_0YGNodeGetHasNewLayout(ABI33_0_0YGNodeRef node) {
  return node->getHasNewLayout();
}

void ABI33_0_0YGConfigSetPrintTreeFlag(ABI33_0_0YGConfigRef config, bool enabled) {
  config->printTree = enabled;
}

void ABI33_0_0YGNodeSetHasNewLayout(ABI33_0_0YGNodeRef node, bool hasNewLayout) {
  node->setHasNewLayout(hasNewLayout);
}

ABI33_0_0YGNodeType ABI33_0_0YGNodeGetNodeType(ABI33_0_0YGNodeRef node) {
  return node->getNodeType();
}

void ABI33_0_0YGNodeSetNodeType(ABI33_0_0YGNodeRef node, ABI33_0_0YGNodeType nodeType) {
  return node->setNodeType(nodeType);
}

bool ABI33_0_0YGNodeIsDirty(ABI33_0_0YGNodeRef node) {
  return node->isDirty();
}

bool ABI33_0_0YGNodeLayoutGetDidUseLegacyFlag(const ABI33_0_0YGNodeRef node) {
  return node->didUseLegacyFlag();
}

void ABI33_0_0YGNodeMarkDirtyAndPropogateToDescendants(const ABI33_0_0YGNodeRef node) {
  return node->markDirtyAndPropogateDownwards();
}

int32_t gNodeInstanceCount = 0;
int32_t gConfigInstanceCount = 0;

WIN_EXPORT ABI33_0_0YGNodeRef ABI33_0_0YGNodeNewWithConfig(const ABI33_0_0YGConfigRef config) {
  const ABI33_0_0YGNodeRef node = new ABI33_0_0YGNode();
  ABI33_0_0YGAssertWithConfig(
      config, node != nullptr, "Could not allocate memory for node");
  gNodeInstanceCount++;

  if (config->useWebDefaults) {
    node->setStyleFlexDirection(ABI33_0_0YGFlexDirectionRow);
    node->setStyleAlignContent(ABI33_0_0YGAlignStretch);
  }
  node->setConfig(config);
  return node;
}

ABI33_0_0YGConfigRef ABI33_0_0YGConfigGetDefault() {
  static ABI33_0_0YGConfigRef defaultConfig = ABI33_0_0YGConfigNew();
  return defaultConfig;
}

ABI33_0_0YGNodeRef ABI33_0_0YGNodeNew(void) {
  return ABI33_0_0YGNodeNewWithConfig(ABI33_0_0YGConfigGetDefault());
}

ABI33_0_0YGNodeRef ABI33_0_0YGNodeClone(ABI33_0_0YGNodeRef oldNode) {
  ABI33_0_0YGNodeRef node = new ABI33_0_0YGNode(*oldNode);
  ABI33_0_0YGAssertWithConfig(
      oldNode->getConfig(),
      node != nullptr,
      "Could not allocate memory for node");
  gNodeInstanceCount++;
  node->setOwner(nullptr);
  return node;
}

static ABI33_0_0YGConfigRef ABI33_0_0YGConfigClone(const ABI33_0_0YGConfig& oldConfig) {
  const ABI33_0_0YGConfigRef config = new ABI33_0_0YGConfig(oldConfig);
  ABI33_0_0YGAssert(config != nullptr, "Could not allocate memory for config");
  if (config == nullptr) {
    abort();
  }
  gConfigInstanceCount++;
  return config;
}

static ABI33_0_0YGNodeRef ABI33_0_0YGNodeDeepClone(ABI33_0_0YGNodeRef oldNode) {
  ABI33_0_0YGNodeRef node = ABI33_0_0YGNodeClone(oldNode);
  ABI33_0_0YGVector vec = ABI33_0_0YGVector();
  vec.reserve(oldNode->getChildren().size());
  ABI33_0_0YGNodeRef childNode = nullptr;
  for (auto* item : oldNode->getChildren()) {
    childNode = ABI33_0_0YGNodeDeepClone(item);
    childNode->setOwner(node);
    vec.push_back(childNode);
  }
  node->setChildren(vec);

  if (oldNode->getConfig() != nullptr) {
    node->setConfig(ABI33_0_0YGConfigClone(*(oldNode->getConfig())));
  }

  return node;
}

void ABI33_0_0YGNodeFree(const ABI33_0_0YGNodeRef node) {
  if (ABI33_0_0YGNodeRef owner = node->getOwner()) {
    owner->removeChild(node);
    node->setOwner(nullptr);
  }

  const uint32_t childCount = ABI33_0_0YGNodeGetChildCount(node);
  for (uint32_t i = 0; i < childCount; i++) {
    const ABI33_0_0YGNodeRef child = ABI33_0_0YGNodeGetChild(node, i);
    child->setOwner(nullptr);
  }

  node->clearChildren();
  delete node;
  gNodeInstanceCount--;
}

static void ABI33_0_0YGConfigFreeRecursive(const ABI33_0_0YGNodeRef root) {
  if (root->getConfig() != nullptr) {
    gConfigInstanceCount--;
    delete root->getConfig();
  }
  // Delete configs recursively for childrens
  for (auto* child : root->getChildren()) {
    ABI33_0_0YGConfigFreeRecursive(child);
  }
}

void ABI33_0_0YGNodeFreeRecursiveWithCleanupFunc(
    const ABI33_0_0YGNodeRef root,
    ABI33_0_0YGNodeCleanupFunc cleanup) {
  while (ABI33_0_0YGNodeGetChildCount(root) > 0) {
    const ABI33_0_0YGNodeRef child = ABI33_0_0YGNodeGetChild(root, 0);
    if (child->getOwner() != root) {
      // Don't free shared nodes that we don't own.
      break;
    }
    ABI33_0_0YGNodeRemoveChild(root, child);
    ABI33_0_0YGNodeFreeRecursive(child);
  }
  if (cleanup != nullptr) {
    cleanup(root);
  }
  ABI33_0_0YGNodeFree(root);
}

void ABI33_0_0YGNodeFreeRecursive(const ABI33_0_0YGNodeRef root) {
  return ABI33_0_0YGNodeFreeRecursiveWithCleanupFunc(root, nullptr);
}

void ABI33_0_0YGNodeReset(const ABI33_0_0YGNodeRef node) {
  ABI33_0_0YGAssertWithNode(
      node,
      ABI33_0_0YGNodeGetChildCount(node) == 0,
      "Cannot reset a node which still has children attached");
  ABI33_0_0YGAssertWithNode(
      node,
      node->getOwner() == nullptr,
      "Cannot reset a node still attached to a owner");

  node->clearChildren();

  const ABI33_0_0YGConfigRef config = node->getConfig();
  *node = ABI33_0_0YGNode();
  if (config->useWebDefaults) {
    node->setStyleFlexDirection(ABI33_0_0YGFlexDirectionRow);
    node->setStyleAlignContent(ABI33_0_0YGAlignStretch);
  }
  node->setConfig(config);
}

int32_t ABI33_0_0YGNodeGetInstanceCount(void) {
  return gNodeInstanceCount;
}

int32_t ABI33_0_0YGConfigGetInstanceCount(void) {
  return gConfigInstanceCount;
}

ABI33_0_0YGConfigRef ABI33_0_0YGConfigNew(void) {
#ifdef ANDROID
  const ABI33_0_0YGConfigRef config = new ABI33_0_0YGConfig(ABI33_0_0YGAndroidLog);
#else
  const ABI33_0_0YGConfigRef config = new ABI33_0_0YGConfig(ABI33_0_0YGDefaultLog);
#endif
  gConfigInstanceCount++;
  return config;
}

void ABI33_0_0YGConfigFree(const ABI33_0_0YGConfigRef config) {
  delete config;
  gConfigInstanceCount--;
}

void ABI33_0_0YGConfigCopy(const ABI33_0_0YGConfigRef dest, const ABI33_0_0YGConfigRef src) {
  memcpy(dest, src, sizeof(ABI33_0_0YGConfig));
}

void ABI33_0_0YGNodeSetIsReferenceBaseline(ABI33_0_0YGNodeRef node, bool isReferenceBaseline) {
  if (node->isReferenceBaseline() != isReferenceBaseline) {
    node->setIsReferenceBaseline(isReferenceBaseline);
    node->markDirtyAndPropogate();
  }
}

bool ABI33_0_0YGNodeIsReferenceBaseline(ABI33_0_0YGNodeRef node) {
  return node->isReferenceBaseline();
}

void ABI33_0_0YGNodeInsertChild(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGNodeRef child,
    const uint32_t index) {
  ABI33_0_0YGAssertWithNode(
      node,
      child->getOwner() == nullptr,
      "Child already has a owner, it must be removed first.");

  ABI33_0_0YGAssertWithNode(
      node,
      node->getMeasure() == nullptr,
      "Cannot add child: Nodes with measure functions cannot have children.");

  node->cloneChildrenIfNeeded();
  node->insertChild(child, index);
  ABI33_0_0YGNodeRef owner = child->getOwner() ? nullptr : node;
  child->setOwner(owner);
  node->markDirtyAndPropogate();
}

void ABI33_0_0YGNodeRemoveChild(const ABI33_0_0YGNodeRef owner, const ABI33_0_0YGNodeRef excludedChild) {
  // This algorithm is a forked variant from cloneChildrenIfNeeded in ABI33_0_0YGNode
  // that excludes a child.
  const uint32_t childCount = ABI33_0_0YGNodeGetChildCount(owner);

  if (childCount == 0) {
    // This is an empty set. Nothing to remove.
    return;
  }
  const ABI33_0_0YGNodeRef firstChild = ABI33_0_0YGNodeGetChild(owner, 0);
  if (firstChild->getOwner() == owner) {
    // If the first child has this node as its owner, we assume that it is
    // already unique. We can now try to delete a child in this list.
    if (owner->removeChild(excludedChild)) {
      excludedChild->setLayout(
          ABI33_0_0YGNode().getLayout()); // layout is no longer valid
      excludedChild->setOwner(nullptr);
      owner->markDirtyAndPropogate();
    }
    return;
  }
  // Otherwise we have to clone the node list except for the child we're trying
  // to delete. We don't want to simply clone all children, because then the
  // host will need to free the clone of the child that was just deleted.
  const ABI33_0_0YGCloneNodeFunc cloneNodeCallback =
      owner->getConfig()->cloneNodeCallback;
  uint32_t nextInsertIndex = 0;
  for (uint32_t i = 0; i < childCount; i++) {
    const ABI33_0_0YGNodeRef oldChild = owner->getChild(i);
    if (excludedChild == oldChild) {
      // Ignore the deleted child. Don't reset its layout or owner since it is
      // still valid in the other owner. However, since this owner has now
      // changed, we need to mark it as dirty.
      owner->markDirtyAndPropogate();
      continue;
    }
    ABI33_0_0YGNodeRef newChild = nullptr;
    if (cloneNodeCallback) {
      newChild = cloneNodeCallback(oldChild, owner, nextInsertIndex);
    }
    if (newChild == nullptr) {
      newChild = ABI33_0_0YGNodeClone(oldChild);
    }
    owner->replaceChild(newChild, nextInsertIndex);
    newChild->setOwner(owner);

    nextInsertIndex++;
  }
  while (nextInsertIndex < childCount) {
    owner->removeChild(nextInsertIndex);
    nextInsertIndex++;
  }
}

void ABI33_0_0YGNodeRemoveAllChildren(const ABI33_0_0YGNodeRef owner) {
  const uint32_t childCount = ABI33_0_0YGNodeGetChildCount(owner);
  if (childCount == 0) {
    // This is an empty set already. Nothing to do.
    return;
  }
  const ABI33_0_0YGNodeRef firstChild = ABI33_0_0YGNodeGetChild(owner, 0);
  if (firstChild->getOwner() == owner) {
    // If the first child has this node as its owner, we assume that this child
    // set is unique.
    for (uint32_t i = 0; i < childCount; i++) {
      const ABI33_0_0YGNodeRef oldChild = ABI33_0_0YGNodeGetChild(owner, i);
      oldChild->setLayout(ABI33_0_0YGNode().getLayout()); // layout is no longer valid
      oldChild->setOwner(nullptr);
    }
    owner->clearChildren();
    owner->markDirtyAndPropogate();
    return;
  }
  // Otherwise, we are not the owner of the child set. We don't have to do
  // anything to clear it.
  owner->setChildren(ABI33_0_0YGVector());
  owner->markDirtyAndPropogate();
}

static void ABI33_0_0YGNodeSetChildrenInternal(
    ABI33_0_0YGNodeRef const owner,
    const std::vector<ABI33_0_0YGNodeRef>& children) {
  if (!owner) {
    return;
  }
  if (children.size() == 0) {
    if (ABI33_0_0YGNodeGetChildCount(owner) > 0) {
      for (ABI33_0_0YGNodeRef const child : owner->getChildren()) {
        child->setLayout(ABI33_0_0YGLayout());
        child->setOwner(nullptr);
      }
      owner->setChildren(ABI33_0_0YGVector());
      owner->markDirtyAndPropogate();
    }
  } else {
    if (ABI33_0_0YGNodeGetChildCount(owner) > 0) {
      for (ABI33_0_0YGNodeRef const oldChild : owner->getChildren()) {
        // Our new children may have nodes in common with the old children. We
        // don't reset these common nodes.
        if (std::find(children.begin(), children.end(), oldChild) ==
            children.end()) {
          oldChild->setLayout(ABI33_0_0YGLayout());
          oldChild->setOwner(nullptr);
        }
      }
    }
    owner->setChildren(children);
    for (ABI33_0_0YGNodeRef child : children) {
      child->setOwner(owner);
    }
    owner->markDirtyAndPropogate();
  }
}

void ABI33_0_0YGNodeSetChildren(
    ABI33_0_0YGNodeRef const owner,
    const ABI33_0_0YGNodeRef c[],
    const uint32_t count) {
  const ABI33_0_0YGVector children = {c, c + count};
  ABI33_0_0YGNodeSetChildrenInternal(owner, children);
}

void ABI33_0_0YGNodeSetChildren(
    ABI33_0_0YGNodeRef const owner,
    const std::vector<ABI33_0_0YGNodeRef>& children) {
  ABI33_0_0YGNodeSetChildrenInternal(owner, children);
}

ABI33_0_0YGNodeRef ABI33_0_0YGNodeGetChild(const ABI33_0_0YGNodeRef node, const uint32_t index) {
  if (index < node->getChildren().size()) {
    return node->getChild(index);
  }
  return nullptr;
}

uint32_t ABI33_0_0YGNodeGetChildCount(const ABI33_0_0YGNodeRef node) {
  return static_cast<uint32_t>(node->getChildren().size());
}

ABI33_0_0YGNodeRef ABI33_0_0YGNodeGetOwner(const ABI33_0_0YGNodeRef node) {
  return node->getOwner();
}

ABI33_0_0YGNodeRef ABI33_0_0YGNodeGetParent(const ABI33_0_0YGNodeRef node) {
  return node->getOwner();
}

void ABI33_0_0YGNodeMarkDirty(const ABI33_0_0YGNodeRef node) {
  ABI33_0_0YGAssertWithNode(
      node,
      node->getMeasure() != nullptr,
      "Only leaf nodes with custom measure functions"
      "should manually mark themselves as dirty");

  node->markDirtyAndPropogate();
}

void ABI33_0_0YGNodeCopyStyle(const ABI33_0_0YGNodeRef dstNode, const ABI33_0_0YGNodeRef srcNode) {
  if (!(dstNode->getStyle() == srcNode->getStyle())) {
    dstNode->setStyle(srcNode->getStyle());
    dstNode->markDirtyAndPropogate();
  }
}

float ABI33_0_0YGNodeStyleGetFlexGrow(const ABI33_0_0YGNodeRef node) {
  return node->getStyle().flexGrow.isUndefined()
      ? kDefaultFlexGrow
      : node->getStyle().flexGrow.unwrap();
}

float ABI33_0_0YGNodeStyleGetFlexShrink(const ABI33_0_0YGNodeRef node) {
  return node->getStyle().flexShrink.isUndefined()
      ? (node->getConfig()->useWebDefaults ? kWebDefaultFlexShrink
                                           : kDefaultFlexShrink)
      : node->getStyle().flexShrink.unwrap();
}

namespace {

struct Value {
  template <ABI33_0_0YGUnit U>
  static detail::CompactValue create(float value) {
    return detail::CompactValue::ofMaybe<U>(value);
  }
};

template <>
inline detail::CompactValue Value::create<ABI33_0_0YGUnitUndefined>(float) {
  return detail::CompactValue::ofUndefined();
}

template <>
inline detail::CompactValue Value::create<ABI33_0_0YGUnitAuto>(float) {
  return detail::CompactValue::ofAuto();
}

template <ABI33_0_0YGStyle::Dimensions ABI33_0_0YGStyle::*P>
struct DimensionProp {
  template <ABI33_0_0YGDimension idx>
  static ABI33_0_0YGValue get(ABI33_0_0YGNodeRef node) {
    ABI33_0_0YGValue value = (node->getStyle().*P)[idx];
    if (value.unit == ABI33_0_0YGUnitUndefined || value.unit == ABI33_0_0YGUnitAuto) {
      value.value = ABI33_0_0YGUndefined;
    }
    return value;
  }

  template <ABI33_0_0YGDimension idx, ABI33_0_0YGUnit U>
  static void set(ABI33_0_0YGNodeRef node, float newValue) {
    auto value = Value::create<U>(newValue);
    if ((node->getStyle().*P)[idx] != value) {
      (node->getStyle().*P)[idx] = value;
      node->markDirtyAndPropogate();
    }
  }
};

} // namespace

#define ABI33_0_0YG_NODE_STYLE_PROPERTY_SETTER_UNIT_AUTO_IMPL(                      \
    type, name, paramName, instanceName)                                   \
  void ABI33_0_0YGNodeStyleSet##name(const ABI33_0_0YGNodeRef node, const type paramName) {  \
    auto value = detail::CompactValue::ofMaybe<ABI33_0_0YGUnitPoint>(paramName);    \
    if (node->getStyle().instanceName != value) {                          \
      node->getStyle().instanceName = value;                               \
      node->markDirtyAndPropogate();                                       \
    }                                                                      \
  }                                                                        \
                                                                           \
  void ABI33_0_0YGNodeStyleSet##name##Percent(                                      \
      const ABI33_0_0YGNodeRef node, const type paramName) {                        \
    auto value = detail::CompactValue::ofMaybe<ABI33_0_0YGUnitPercent>(paramName);  \
    if (node->getStyle().instanceName != value) {                          \
      node->getStyle().instanceName = value;                               \
      node->markDirtyAndPropogate();                                       \
    }                                                                      \
  }                                                                        \
                                                                           \
  void ABI33_0_0YGNodeStyleSet##name##Auto(const ABI33_0_0YGNodeRef node) {                  \
    if (node->getStyle().instanceName != detail::CompactValue::ofAuto()) { \
      node->getStyle().instanceName = detail::CompactValue::ofAuto();      \
      node->markDirtyAndPropogate();                                       \
    }                                                                      \
  }

#define ABI33_0_0YG_NODE_STYLE_PROPERTY_UNIT_AUTO_IMPL(                       \
    type, name, paramName, instanceName)                             \
  ABI33_0_0YG_NODE_STYLE_PROPERTY_SETTER_UNIT_AUTO_IMPL(                      \
      float, name, paramName, instanceName)                          \
                                                                     \
  type ABI33_0_0YGNodeStyleGet##name(const ABI33_0_0YGNodeRef node) {                  \
    ABI33_0_0YGValue value = node->getStyle().instanceName;                   \
    if (value.unit == ABI33_0_0YGUnitUndefined || value.unit == ABI33_0_0YGUnitAuto) { \
      value.value = ABI33_0_0YGUndefined;                                     \
    }                                                                \
    return value;                                                    \
  }

#define ABI33_0_0YG_NODE_STYLE_EDGE_PROPERTY_UNIT_AUTO_IMPL(type, name, instanceName) \
  void ABI33_0_0YGNodeStyleSet##name##Auto(const ABI33_0_0YGNodeRef node, const ABI33_0_0YGEdge edge) { \
    if (node->getStyle().instanceName[edge] !=                               \
        detail::CompactValue::ofAuto()) {                                    \
      node->getStyle().instanceName[edge] = detail::CompactValue::ofAuto();  \
      node->markDirtyAndPropogate();                                         \
    }                                                                        \
  }

#define ABI33_0_0YG_NODE_STYLE_EDGE_PROPERTY_UNIT_IMPL(                            \
    type, name, paramName, instanceName)                                  \
  void ABI33_0_0YGNodeStyleSet##name(                                              \
      const ABI33_0_0YGNodeRef node, const ABI33_0_0YGEdge edge, const float paramName) {   \
    auto value = detail::CompactValue::ofMaybe<ABI33_0_0YGUnitPoint>(paramName);   \
    if (node->getStyle().instanceName[edge] != value) {                   \
      node->getStyle().instanceName[edge] = value;                        \
      node->markDirtyAndPropogate();                                      \
    }                                                                     \
  }                                                                       \
                                                                          \
  void ABI33_0_0YGNodeStyleSet##name##Percent(                                     \
      const ABI33_0_0YGNodeRef node, const ABI33_0_0YGEdge edge, const float paramName) {   \
    auto value = detail::CompactValue::ofMaybe<ABI33_0_0YGUnitPercent>(paramName); \
    if (node->getStyle().instanceName[edge] != value) {                   \
      node->getStyle().instanceName[edge] = value;                        \
      node->markDirtyAndPropogate();                                      \
    }                                                                     \
  }                                                                       \
                                                                          \
  type ABI33_0_0YGNodeStyleGet##name(const ABI33_0_0YGNodeRef node, const ABI33_0_0YGEdge edge) {    \
    ABI33_0_0YGValue value = node->getStyle().instanceName[edge];                  \
    if (value.unit == ABI33_0_0YGUnitUndefined || value.unit == ABI33_0_0YGUnitAuto) {      \
      value.value = ABI33_0_0YGUndefined;                                          \
    }                                                                     \
    return value;                                                         \
  }

#define ABI33_0_0YG_NODE_LAYOUT_PROPERTY_IMPL(type, name, instanceName) \
  type ABI33_0_0YGNodeLayoutGet##name(const ABI33_0_0YGNodeRef node) {           \
    return node->getLayout().instanceName;                     \
  }

#define ABI33_0_0YG_NODE_LAYOUT_RESOLVED_PROPERTY_IMPL(type, name, instanceName) \
  type ABI33_0_0YGNodeLayoutGet##name(const ABI33_0_0YGNodeRef node, const ABI33_0_0YGEdge edge) { \
    ABI33_0_0YGAssertWithNode(                                                   \
        node,                                                           \
        edge <= ABI33_0_0YGEdgeEnd,                                              \
        "Cannot get layout properties of multi-edge shorthands");       \
                                                                        \
    if (edge == ABI33_0_0YGEdgeLeft) {                                           \
      if (node->getLayout().direction == ABI33_0_0YGDirectionRTL) {              \
        return node->getLayout().instanceName[ABI33_0_0YGEdgeEnd];               \
      } else {                                                          \
        return node->getLayout().instanceName[ABI33_0_0YGEdgeStart];             \
      }                                                                 \
    }                                                                   \
                                                                        \
    if (edge == ABI33_0_0YGEdgeRight) {                                          \
      if (node->getLayout().direction == ABI33_0_0YGDirectionRTL) {              \
        return node->getLayout().instanceName[ABI33_0_0YGEdgeStart];             \
      } else {                                                          \
        return node->getLayout().instanceName[ABI33_0_0YGEdgeEnd];               \
      }                                                                 \
    }                                                                   \
                                                                        \
    return node->getLayout().instanceName[edge];                        \
  }

#define ABI33_0_0YG_NODE_STYLE_SET(node, property, value) \
  if (node->getStyle().property != value) {      \
    node->getStyle().property = value;           \
    node->markDirtyAndPropogate();               \
  }

void ABI33_0_0YGNodeStyleSetDirection(const ABI33_0_0YGNodeRef node, const ABI33_0_0YGDirection value) {
  ABI33_0_0YG_NODE_STYLE_SET(node, direction, value);
}
ABI33_0_0YGDirection ABI33_0_0YGNodeStyleGetDirection(const ABI33_0_0YGNodeRef node) {
  return node->getStyle().direction;
}

void ABI33_0_0YGNodeStyleSetFlexDirection(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGFlexDirection flexDirection) {
  ABI33_0_0YG_NODE_STYLE_SET(node, flexDirection, flexDirection);
}
ABI33_0_0YGFlexDirection ABI33_0_0YGNodeStyleGetFlexDirection(const ABI33_0_0YGNodeRef node) {
  return node->getStyle().flexDirection;
}

void ABI33_0_0YGNodeStyleSetJustifyContent(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGJustify justifyContent) {
  ABI33_0_0YG_NODE_STYLE_SET(node, justifyContent, justifyContent);
}
ABI33_0_0YGJustify ABI33_0_0YGNodeStyleGetJustifyContent(const ABI33_0_0YGNodeRef node) {
  return node->getStyle().justifyContent;
}

void ABI33_0_0YGNodeStyleSetAlignContent(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGAlign alignContent) {
  ABI33_0_0YG_NODE_STYLE_SET(node, alignContent, alignContent);
}
ABI33_0_0YGAlign ABI33_0_0YGNodeStyleGetAlignContent(const ABI33_0_0YGNodeRef node) {
  return node->getStyle().alignContent;
}

void ABI33_0_0YGNodeStyleSetAlignItems(const ABI33_0_0YGNodeRef node, const ABI33_0_0YGAlign alignItems) {
  ABI33_0_0YG_NODE_STYLE_SET(node, alignItems, alignItems);
}
ABI33_0_0YGAlign ABI33_0_0YGNodeStyleGetAlignItems(const ABI33_0_0YGNodeRef node) {
  return node->getStyle().alignItems;
}

void ABI33_0_0YGNodeStyleSetAlignSelf(const ABI33_0_0YGNodeRef node, const ABI33_0_0YGAlign alignSelf) {
  ABI33_0_0YG_NODE_STYLE_SET(node, alignSelf, alignSelf);
}
ABI33_0_0YGAlign ABI33_0_0YGNodeStyleGetAlignSelf(const ABI33_0_0YGNodeRef node) {
  return node->getStyle().alignSelf;
}

void ABI33_0_0YGNodeStyleSetPositionType(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGPositionType positionType) {
  ABI33_0_0YG_NODE_STYLE_SET(node, positionType, positionType);
}
ABI33_0_0YGPositionType ABI33_0_0YGNodeStyleGetPositionType(const ABI33_0_0YGNodeRef node) {
  return node->getStyle().positionType;
}

void ABI33_0_0YGNodeStyleSetFlexWrap(const ABI33_0_0YGNodeRef node, const ABI33_0_0YGWrap flexWrap) {
  ABI33_0_0YG_NODE_STYLE_SET(node, flexWrap, flexWrap);
}
ABI33_0_0YGWrap ABI33_0_0YGNodeStyleGetFlexWrap(const ABI33_0_0YGNodeRef node) {
  return node->getStyle().flexWrap;
}

void ABI33_0_0YGNodeStyleSetOverflow(const ABI33_0_0YGNodeRef node, const ABI33_0_0YGOverflow overflow) {
  ABI33_0_0YG_NODE_STYLE_SET(node, overflow, overflow);
}
ABI33_0_0YGOverflow ABI33_0_0YGNodeStyleGetOverflow(const ABI33_0_0YGNodeRef node) {
  return node->getStyle().overflow;
}

void ABI33_0_0YGNodeStyleSetDisplay(const ABI33_0_0YGNodeRef node, const ABI33_0_0YGDisplay display) {
  ABI33_0_0YG_NODE_STYLE_SET(node, display, display);
}
ABI33_0_0YGDisplay ABI33_0_0YGNodeStyleGetDisplay(const ABI33_0_0YGNodeRef node) {
  return node->getStyle().display;
}

// TODO(T26792433): Change the API to accept ABI33_0_0YGFloatOptional.
void ABI33_0_0YGNodeStyleSetFlex(const ABI33_0_0YGNodeRef node, const float flex) {
  if (node->getStyle().flex != flex) {
    node->getStyle().flex =
        ABI33_0_0YGFloatIsUndefined(flex) ? ABI33_0_0YGFloatOptional() : ABI33_0_0YGFloatOptional(flex);
    node->markDirtyAndPropogate();
  }
}

// TODO(T26792433): Change the API to accept ABI33_0_0YGFloatOptional.
float ABI33_0_0YGNodeStyleGetFlex(const ABI33_0_0YGNodeRef node) {
  return node->getStyle().flex.isUndefined() ? ABI33_0_0YGUndefined
                                             : node->getStyle().flex.unwrap();
}

// TODO(T26792433): Change the API to accept ABI33_0_0YGFloatOptional.
void ABI33_0_0YGNodeStyleSetFlexGrow(const ABI33_0_0YGNodeRef node, const float flexGrow) {
  if (node->getStyle().flexGrow != flexGrow) {
    node->getStyle().flexGrow = ABI33_0_0YGFloatIsUndefined(flexGrow)
        ? ABI33_0_0YGFloatOptional()
        : ABI33_0_0YGFloatOptional(flexGrow);
    node->markDirtyAndPropogate();
  }
}

// TODO(T26792433): Change the API to accept ABI33_0_0YGFloatOptional.
void ABI33_0_0YGNodeStyleSetFlexShrink(const ABI33_0_0YGNodeRef node, const float flexShrink) {
  if (node->getStyle().flexShrink != flexShrink) {
    node->getStyle().flexShrink = ABI33_0_0YGFloatIsUndefined(flexShrink)
        ? ABI33_0_0YGFloatOptional()
        : ABI33_0_0YGFloatOptional(flexShrink);
    node->markDirtyAndPropogate();
  }
}

ABI33_0_0YGValue ABI33_0_0YGNodeStyleGetFlexBasis(const ABI33_0_0YGNodeRef node) {
  ABI33_0_0YGValue flexBasis = node->getStyle().flexBasis;
  if (flexBasis.unit == ABI33_0_0YGUnitUndefined || flexBasis.unit == ABI33_0_0YGUnitAuto) {
    // TODO(T26792433): Get rid off the use of ABI33_0_0YGUndefined at client side
    flexBasis.value = ABI33_0_0YGUndefined;
  }
  return flexBasis;
}

void ABI33_0_0YGNodeStyleSetFlexBasis(const ABI33_0_0YGNodeRef node, const float flexBasis) {
  auto value = detail::CompactValue::ofMaybe<ABI33_0_0YGUnitPoint>(flexBasis);
  if (node->getStyle().flexBasis != value) {
    node->getStyle().flexBasis = value;
    node->markDirtyAndPropogate();
  }
}

void ABI33_0_0YGNodeStyleSetFlexBasisPercent(
    const ABI33_0_0YGNodeRef node,
    const float flexBasisPercent) {
  auto value = detail::CompactValue::ofMaybe<ABI33_0_0YGUnitPercent>(flexBasisPercent);
  if (node->getStyle().flexBasis != value) {
    node->getStyle().flexBasis = value;
    node->markDirtyAndPropogate();
  }
}

void ABI33_0_0YGNodeStyleSetFlexBasisAuto(const ABI33_0_0YGNodeRef node) {
  if (node->getStyle().flexBasis != detail::CompactValue::ofAuto()) {
    node->getStyle().flexBasis = detail::CompactValue::ofAuto();
    node->markDirtyAndPropogate();
  }
}

ABI33_0_0YG_NODE_STYLE_EDGE_PROPERTY_UNIT_IMPL(ABI33_0_0YGValue, Position, position, position);
ABI33_0_0YG_NODE_STYLE_EDGE_PROPERTY_UNIT_IMPL(ABI33_0_0YGValue, Margin, margin, margin);
ABI33_0_0YG_NODE_STYLE_EDGE_PROPERTY_UNIT_AUTO_IMPL(ABI33_0_0YGValue, Margin, margin);
ABI33_0_0YG_NODE_STYLE_EDGE_PROPERTY_UNIT_IMPL(ABI33_0_0YGValue, Padding, padding, padding);

// TODO(T26792433): Change the API to accept ABI33_0_0YGFloatOptional.
void ABI33_0_0YGNodeStyleSetBorder(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGEdge edge,
    const float border) {
  auto value = detail::CompactValue::ofMaybe<ABI33_0_0YGUnitPoint>(border);
  if (node->getStyle().border[edge] != value) {
    node->getStyle().border[edge] = value;
    node->markDirtyAndPropogate();
  }
}

float ABI33_0_0YGNodeStyleGetBorder(const ABI33_0_0YGNodeRef node, const ABI33_0_0YGEdge edge) {
  if (node->getStyle().border[edge].isUndefined() ||
      node->getStyle().border[edge].isAuto()) {
    // TODO(T26792433): Rather than returning ABI33_0_0YGUndefined, change the api to
    // return ABI33_0_0YGFloatOptional.
    return ABI33_0_0YGUndefined;
  }

  auto border = (ABI33_0_0YGValue) node->getStyle().border[edge];
  return border.value;
}

// Yoga specific properties, not compatible with flexbox specification

// TODO(T26792433): Change the API to accept ABI33_0_0YGFloatOptional.
float ABI33_0_0YGNodeStyleGetAspectRatio(const ABI33_0_0YGNodeRef node) {
  const ABI33_0_0YGFloatOptional op = node->getStyle().aspectRatio;
  return op.isUndefined() ? ABI33_0_0YGUndefined : op.unwrap();
}

// TODO(T26792433): Change the API to accept ABI33_0_0YGFloatOptional.
void ABI33_0_0YGNodeStyleSetAspectRatio(const ABI33_0_0YGNodeRef node, const float aspectRatio) {
  if (node->getStyle().aspectRatio != aspectRatio) {
    node->getStyle().aspectRatio = ABI33_0_0YGFloatOptional(aspectRatio);
    node->markDirtyAndPropogate();
  }
}

ABI33_0_0YG_NODE_STYLE_PROPERTY_UNIT_AUTO_IMPL(
    ABI33_0_0YGValue,
    Width,
    width,
    dimensions[ABI33_0_0YGDimensionWidth]);
ABI33_0_0YG_NODE_STYLE_PROPERTY_UNIT_AUTO_IMPL(
    ABI33_0_0YGValue,
    Height,
    height,
    dimensions[ABI33_0_0YGDimensionHeight]);

void ABI33_0_0YGNodeStyleSetMinWidth(const ABI33_0_0YGNodeRef node, const float minWidth) {
  DimensionProp<&ABI33_0_0YGStyle::minDimensions>::set<ABI33_0_0YGDimensionWidth, ABI33_0_0YGUnitPoint>(
      node, minWidth);
}
void ABI33_0_0YGNodeStyleSetMinWidthPercent(const ABI33_0_0YGNodeRef node, const float minWidth) {
  DimensionProp<&ABI33_0_0YGStyle::minDimensions>::set<ABI33_0_0YGDimensionWidth, ABI33_0_0YGUnitPercent>(
      node, minWidth);
}
ABI33_0_0YGValue ABI33_0_0YGNodeStyleGetMinWidth(const ABI33_0_0YGNodeRef node) {
  return DimensionProp<&ABI33_0_0YGStyle::minDimensions>::get<ABI33_0_0YGDimensionWidth>(node);
};

void ABI33_0_0YGNodeStyleSetMinHeight(const ABI33_0_0YGNodeRef node, const float minHeight) {
  DimensionProp<&ABI33_0_0YGStyle::minDimensions>::set<ABI33_0_0YGDimensionHeight, ABI33_0_0YGUnitPoint>(
      node, minHeight);
}
void ABI33_0_0YGNodeStyleSetMinHeightPercent(
    const ABI33_0_0YGNodeRef node,
    const float minHeight) {
  DimensionProp<&ABI33_0_0YGStyle::minDimensions>::set<ABI33_0_0YGDimensionHeight, ABI33_0_0YGUnitPercent>(
      node, minHeight);
}
ABI33_0_0YGValue ABI33_0_0YGNodeStyleGetMinHeight(const ABI33_0_0YGNodeRef node) {
  return DimensionProp<&ABI33_0_0YGStyle::minDimensions>::get<ABI33_0_0YGDimensionHeight>(node);
};

void ABI33_0_0YGNodeStyleSetMaxWidth(const ABI33_0_0YGNodeRef node, const float maxWidth) {
  DimensionProp<&ABI33_0_0YGStyle::maxDimensions>::set<ABI33_0_0YGDimensionWidth, ABI33_0_0YGUnitPoint>(
      node, maxWidth);
}
void ABI33_0_0YGNodeStyleSetMaxWidthPercent(const ABI33_0_0YGNodeRef node, const float maxWidth) {
  DimensionProp<&ABI33_0_0YGStyle::maxDimensions>::set<ABI33_0_0YGDimensionWidth, ABI33_0_0YGUnitPercent>(
      node, maxWidth);
}
ABI33_0_0YGValue ABI33_0_0YGNodeStyleGetMaxWidth(const ABI33_0_0YGNodeRef node) {
  return DimensionProp<&ABI33_0_0YGStyle::maxDimensions>::get<ABI33_0_0YGDimensionWidth>(node);
};

void ABI33_0_0YGNodeStyleSetMaxHeight(const ABI33_0_0YGNodeRef node, const float maxHeight) {
  DimensionProp<&ABI33_0_0YGStyle::maxDimensions>::set<ABI33_0_0YGDimensionHeight, ABI33_0_0YGUnitPoint>(
      node, maxHeight);
}
void ABI33_0_0YGNodeStyleSetMaxHeightPercent(
    const ABI33_0_0YGNodeRef node,
    const float maxHeight) {
  DimensionProp<&ABI33_0_0YGStyle::maxDimensions>::set<ABI33_0_0YGDimensionHeight, ABI33_0_0YGUnitPercent>(
      node, maxHeight);
}
ABI33_0_0YGValue ABI33_0_0YGNodeStyleGetMaxHeight(const ABI33_0_0YGNodeRef node) {
  return DimensionProp<&ABI33_0_0YGStyle::maxDimensions>::get<ABI33_0_0YGDimensionHeight>(node);
};

ABI33_0_0YG_NODE_LAYOUT_PROPERTY_IMPL(float, Left, position[ABI33_0_0YGEdgeLeft]);
ABI33_0_0YG_NODE_LAYOUT_PROPERTY_IMPL(float, Top, position[ABI33_0_0YGEdgeTop]);
ABI33_0_0YG_NODE_LAYOUT_PROPERTY_IMPL(float, Right, position[ABI33_0_0YGEdgeRight]);
ABI33_0_0YG_NODE_LAYOUT_PROPERTY_IMPL(float, Bottom, position[ABI33_0_0YGEdgeBottom]);
ABI33_0_0YG_NODE_LAYOUT_PROPERTY_IMPL(float, Width, dimensions[ABI33_0_0YGDimensionWidth]);
ABI33_0_0YG_NODE_LAYOUT_PROPERTY_IMPL(float, Height, dimensions[ABI33_0_0YGDimensionHeight]);
ABI33_0_0YG_NODE_LAYOUT_PROPERTY_IMPL(ABI33_0_0YGDirection, Direction, direction);
ABI33_0_0YG_NODE_LAYOUT_PROPERTY_IMPL(bool, HadOverflow, hadOverflow);

ABI33_0_0YG_NODE_LAYOUT_RESOLVED_PROPERTY_IMPL(float, Margin, margin);
ABI33_0_0YG_NODE_LAYOUT_RESOLVED_PROPERTY_IMPL(float, Border, border);
ABI33_0_0YG_NODE_LAYOUT_RESOLVED_PROPERTY_IMPL(float, Padding, padding);

bool ABI33_0_0YGNodeLayoutGetDidLegacyStretchFlagAffectLayout(const ABI33_0_0YGNodeRef node) {
  return node->getLayout().doesLegacyStretchFlagAffectsLayout;
}

uint32_t gCurrentGenerationCount = 0;

bool ABI33_0_0YGLayoutNodeInternal(
    const ABI33_0_0YGNodeRef node,
    const float availableWidth,
    const float availableHeight,
    const ABI33_0_0YGDirection ownerDirection,
    const ABI33_0_0YGMeasureMode widthMeasureMode,
    const ABI33_0_0YGMeasureMode heightMeasureMode,
    const float ownerWidth,
    const float ownerHeight,
    const bool performLayout,
    const char* reason,
    const ABI33_0_0YGConfigRef config,
    ABI33_0_0YGMarkerLayoutData& layoutMarkerData);

static void ABI33_0_0YGNodePrintInternal(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGPrintOptions options) {
  std::string str;
  facebook::ABI33_0_0yoga::ABI33_0_0YGNodeToString(str, node, options, 0);
  ABI33_0_0YGLog(node, ABI33_0_0YGLogLevelDebug, str.c_str());
}

void ABI33_0_0YGNodePrint(const ABI33_0_0YGNodeRef node, const ABI33_0_0YGPrintOptions options) {
  ABI33_0_0YGNodePrintInternal(node, options);
}

const std::array<ABI33_0_0YGEdge, 4> leading = {
    {ABI33_0_0YGEdgeTop, ABI33_0_0YGEdgeBottom, ABI33_0_0YGEdgeLeft, ABI33_0_0YGEdgeRight}};

const std::array<ABI33_0_0YGEdge, 4> trailing = {
    {ABI33_0_0YGEdgeBottom, ABI33_0_0YGEdgeTop, ABI33_0_0YGEdgeRight, ABI33_0_0YGEdgeLeft}};
static const std::array<ABI33_0_0YGEdge, 4> pos = {{
    ABI33_0_0YGEdgeTop,
    ABI33_0_0YGEdgeBottom,
    ABI33_0_0YGEdgeLeft,
    ABI33_0_0YGEdgeRight,
}};

static const std::array<ABI33_0_0YGDimension, 4> dim = {
    {ABI33_0_0YGDimensionHeight, ABI33_0_0YGDimensionHeight, ABI33_0_0YGDimensionWidth, ABI33_0_0YGDimensionWidth}};

static inline float ABI33_0_0YGNodePaddingAndBorderForAxis(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGFlexDirection axis,
    const float widthSize) {
  return (node->getLeadingPaddingAndBorder(axis, widthSize) +
          node->getTrailingPaddingAndBorder(axis, widthSize))
      .unwrap();
}

static inline ABI33_0_0YGAlign ABI33_0_0YGNodeAlignItem(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGNodeRef child) {
  const ABI33_0_0YGAlign align = child->getStyle().alignSelf == ABI33_0_0YGAlignAuto
      ? node->getStyle().alignItems
      : child->getStyle().alignSelf;
  if (align == ABI33_0_0YGAlignBaseline &&
      ABI33_0_0YGFlexDirectionIsColumn(node->getStyle().flexDirection)) {
    return ABI33_0_0YGAlignFlexStart;
  }
  return align;
}

static float ABI33_0_0YGBaseline(const ABI33_0_0YGNodeRef node) {
  if (node->getBaseline() != nullptr) {
    const float baseline = marker::MarkerSection<ABI33_0_0YGMarkerBaselineFn>::wrap(
        node,
        node->getBaseline(),
        node,
        node->getLayout().measuredDimensions[ABI33_0_0YGDimensionWidth],
        node->getLayout().measuredDimensions[ABI33_0_0YGDimensionHeight]);
    ABI33_0_0YGAssertWithNode(
        node,
        !ABI33_0_0YGFloatIsUndefined(baseline),
        "Expect custom baseline function to not return NaN");
    return baseline;
  }

  ABI33_0_0YGNodeRef baselineChild = nullptr;
  const uint32_t childCount = ABI33_0_0YGNodeGetChildCount(node);
  for (uint32_t i = 0; i < childCount; i++) {
    const ABI33_0_0YGNodeRef child = ABI33_0_0YGNodeGetChild(node, i);
    if (child->getLineIndex() > 0) {
      break;
    }
    if (child->getStyle().positionType == ABI33_0_0YGPositionTypeAbsolute) {
      continue;
    }
    if (ABI33_0_0YGNodeAlignItem(node, child) == ABI33_0_0YGAlignBaseline ||
        child->isReferenceBaseline()) {
      baselineChild = child;
      break;
    }

    if (baselineChild == nullptr) {
      baselineChild = child;
    }
  }

  if (baselineChild == nullptr) {
    return node->getLayout().measuredDimensions[ABI33_0_0YGDimensionHeight];
  }

  const float baseline = ABI33_0_0YGBaseline(baselineChild);
  return baseline + baselineChild->getLayout().position[ABI33_0_0YGEdgeTop];
}

static bool ABI33_0_0YGIsBaselineLayout(const ABI33_0_0YGNodeRef node) {
  if (ABI33_0_0YGFlexDirectionIsColumn(node->getStyle().flexDirection)) {
    return false;
  }
  if (node->getStyle().alignItems == ABI33_0_0YGAlignBaseline) {
    return true;
  }
  const uint32_t childCount = ABI33_0_0YGNodeGetChildCount(node);
  for (uint32_t i = 0; i < childCount; i++) {
    const ABI33_0_0YGNodeRef child = ABI33_0_0YGNodeGetChild(node, i);
    if (child->getStyle().positionType == ABI33_0_0YGPositionTypeRelative &&
        child->getStyle().alignSelf == ABI33_0_0YGAlignBaseline) {
      return true;
    }
  }

  return false;
}

static inline float ABI33_0_0YGNodeDimWithMargin(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGFlexDirection axis,
    const float widthSize) {
  return node->getLayout().measuredDimensions[dim[axis]] +
      (node->getLeadingMargin(axis, widthSize) +
       node->getTrailingMargin(axis, widthSize))
          .unwrap();
}

static inline bool ABI33_0_0YGNodeIsStyleDimDefined(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGFlexDirection axis,
    const float ownerSize) {
  bool isUndefined =
      ABI33_0_0YGFloatIsUndefined(node->getResolvedDimension(dim[axis]).value);
  return !(
      node->getResolvedDimension(dim[axis]).unit == ABI33_0_0YGUnitAuto ||
      node->getResolvedDimension(dim[axis]).unit == ABI33_0_0YGUnitUndefined ||
      (node->getResolvedDimension(dim[axis]).unit == ABI33_0_0YGUnitPoint &&
       !isUndefined && node->getResolvedDimension(dim[axis]).value < 0.0f) ||
      (node->getResolvedDimension(dim[axis]).unit == ABI33_0_0YGUnitPercent &&
       !isUndefined &&
       (node->getResolvedDimension(dim[axis]).value < 0.0f ||
        ABI33_0_0YGFloatIsUndefined(ownerSize))));
}

static inline bool ABI33_0_0YGNodeIsLayoutDimDefined(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGFlexDirection axis) {
  const float value = node->getLayout().measuredDimensions[dim[axis]];
  return !ABI33_0_0YGFloatIsUndefined(value) && value >= 0.0f;
}

static ABI33_0_0YGFloatOptional ABI33_0_0YGNodeBoundAxisWithinMinAndMax(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGFlexDirection axis,
    const ABI33_0_0YGFloatOptional value,
    const float axisSize) {
  ABI33_0_0YGFloatOptional min;
  ABI33_0_0YGFloatOptional max;

  if (ABI33_0_0YGFlexDirectionIsColumn(axis)) {
    min = ABI33_0_0YGResolveValue(
        node->getStyle().minDimensions[ABI33_0_0YGDimensionHeight], axisSize);
    max = ABI33_0_0YGResolveValue(
        node->getStyle().maxDimensions[ABI33_0_0YGDimensionHeight], axisSize);
  } else if (ABI33_0_0YGFlexDirectionIsRow(axis)) {
    min = ABI33_0_0YGResolveValue(
        node->getStyle().minDimensions[ABI33_0_0YGDimensionWidth], axisSize);
    max = ABI33_0_0YGResolveValue(
        node->getStyle().maxDimensions[ABI33_0_0YGDimensionWidth], axisSize);
  }

  if (max >= ABI33_0_0YGFloatOptional{0} && value > max) {
    return max;
  }

  if (min >= ABI33_0_0YGFloatOptional{0} && value < min) {
    return min;
  }

  return value;
}

// Like ABI33_0_0YGNodeBoundAxisWithinMinAndMax but also ensures that the value doesn't
// go below the padding and border amount.
static inline float ABI33_0_0YGNodeBoundAxis(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGFlexDirection axis,
    const float value,
    const float axisSize,
    const float widthSize) {
  return ABI33_0_0YGFloatMax(
      ABI33_0_0YGNodeBoundAxisWithinMinAndMax(
          node, axis, ABI33_0_0YGFloatOptional{value}, axisSize)
          .unwrap(),
      ABI33_0_0YGNodePaddingAndBorderForAxis(node, axis, widthSize));
}

static void ABI33_0_0YGNodeSetChildTrailingPosition(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGNodeRef child,
    const ABI33_0_0YGFlexDirection axis) {
  const float size = child->getLayout().measuredDimensions[dim[axis]];
  child->setLayoutPosition(
      node->getLayout().measuredDimensions[dim[axis]] - size -
          child->getLayout().position[pos[axis]],
      trailing[axis]);
}

static void ABI33_0_0YGConstrainMaxSizeForMode(
    const ABI33_0_0YGNodeRef node,
    const enum ABI33_0_0YGFlexDirection axis,
    const float ownerAxisSize,
    const float ownerWidth,
    ABI33_0_0YGMeasureMode* mode,
    float* size) {
  const ABI33_0_0YGFloatOptional maxSize =
      ABI33_0_0YGResolveValue(node->getStyle().maxDimensions[dim[axis]], ownerAxisSize) +
      ABI33_0_0YGFloatOptional(node->getMarginForAxis(axis, ownerWidth));
  switch (*mode) {
    case ABI33_0_0YGMeasureModeExactly:
    case ABI33_0_0YGMeasureModeAtMost:
      *size = (maxSize.isUndefined() || *size < maxSize.unwrap())
          ? *size
          : maxSize.unwrap();
      break;
    case ABI33_0_0YGMeasureModeUndefined:
      if (!maxSize.isUndefined()) {
        *mode = ABI33_0_0YGMeasureModeAtMost;
        *size = maxSize.unwrap();
      }
      break;
  }
}

static void ABI33_0_0YGNodeComputeFlexBasisForChild(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGNodeRef child,
    const float width,
    const ABI33_0_0YGMeasureMode widthMode,
    const float height,
    const float ownerWidth,
    const float ownerHeight,
    const ABI33_0_0YGMeasureMode heightMode,
    const ABI33_0_0YGDirection direction,
    const ABI33_0_0YGConfigRef config,
    ABI33_0_0YGMarkerLayoutData& layoutMarkerData) {
  const ABI33_0_0YGFlexDirection mainAxis =
      ABI33_0_0YGResolveFlexDirection(node->getStyle().flexDirection, direction);
  const bool isMainAxisRow = ABI33_0_0YGFlexDirectionIsRow(mainAxis);
  const float mainAxisSize = isMainAxisRow ? width : height;
  const float mainAxisownerSize = isMainAxisRow ? ownerWidth : ownerHeight;

  float childWidth;
  float childHeight;
  ABI33_0_0YGMeasureMode childWidthMeasureMode;
  ABI33_0_0YGMeasureMode childHeightMeasureMode;

  const ABI33_0_0YGFloatOptional resolvedFlexBasis =
      ABI33_0_0YGResolveValue(child->resolveFlexBasisPtr(), mainAxisownerSize);
  const bool isRowStyleDimDefined =
      ABI33_0_0YGNodeIsStyleDimDefined(child, ABI33_0_0YGFlexDirectionRow, ownerWidth);
  const bool isColumnStyleDimDefined =
      ABI33_0_0YGNodeIsStyleDimDefined(child, ABI33_0_0YGFlexDirectionColumn, ownerHeight);

  if (!resolvedFlexBasis.isUndefined() && !ABI33_0_0YGFloatIsUndefined(mainAxisSize)) {
    if (child->getLayout().computedFlexBasis.isUndefined() ||
        (ABI33_0_0YGConfigIsExperimentalFeatureEnabled(
             child->getConfig(), ABI33_0_0YGExperimentalFeatureWebFlexBasis) &&
         child->getLayout().computedFlexBasisGeneration !=
             gCurrentGenerationCount)) {
      const ABI33_0_0YGFloatOptional paddingAndBorder = ABI33_0_0YGFloatOptional(
          ABI33_0_0YGNodePaddingAndBorderForAxis(child, mainAxis, ownerWidth));
      child->setLayoutComputedFlexBasis(
          ABI33_0_0YGFloatOptionalMax(resolvedFlexBasis, paddingAndBorder));
    }
  } else if (isMainAxisRow && isRowStyleDimDefined) {
    // The width is definite, so use that as the flex basis.
    const ABI33_0_0YGFloatOptional paddingAndBorder = ABI33_0_0YGFloatOptional(
        ABI33_0_0YGNodePaddingAndBorderForAxis(child, ABI33_0_0YGFlexDirectionRow, ownerWidth));

    child->setLayoutComputedFlexBasis(ABI33_0_0YGFloatOptionalMax(
        ABI33_0_0YGResolveValue(
            child->getResolvedDimension(ABI33_0_0YGDimensionWidth), ownerWidth),
        paddingAndBorder));
  } else if (!isMainAxisRow && isColumnStyleDimDefined) {
    // The height is definite, so use that as the flex basis.
    const ABI33_0_0YGFloatOptional paddingAndBorder =
        ABI33_0_0YGFloatOptional(ABI33_0_0YGNodePaddingAndBorderForAxis(
            child, ABI33_0_0YGFlexDirectionColumn, ownerWidth));
    child->setLayoutComputedFlexBasis(ABI33_0_0YGFloatOptionalMax(
        ABI33_0_0YGResolveValue(
            child->getResolvedDimension(ABI33_0_0YGDimensionHeight), ownerHeight),
        paddingAndBorder));
  } else {
    // Compute the flex basis and hypothetical main size (i.e. the clamped flex
    // basis).
    childWidth = ABI33_0_0YGUndefined;
    childHeight = ABI33_0_0YGUndefined;
    childWidthMeasureMode = ABI33_0_0YGMeasureModeUndefined;
    childHeightMeasureMode = ABI33_0_0YGMeasureModeUndefined;

    auto marginRow =
        child->getMarginForAxis(ABI33_0_0YGFlexDirectionRow, ownerWidth).unwrap();
    auto marginColumn =
        child->getMarginForAxis(ABI33_0_0YGFlexDirectionColumn, ownerWidth).unwrap();

    if (isRowStyleDimDefined) {
      childWidth =
          ABI33_0_0YGResolveValue(
              child->getResolvedDimension(ABI33_0_0YGDimensionWidth), ownerWidth)
              .unwrap() +
          marginRow;
      childWidthMeasureMode = ABI33_0_0YGMeasureModeExactly;
    }
    if (isColumnStyleDimDefined) {
      childHeight =
          ABI33_0_0YGResolveValue(
              child->getResolvedDimension(ABI33_0_0YGDimensionHeight), ownerHeight)
              .unwrap() +
          marginColumn;
      childHeightMeasureMode = ABI33_0_0YGMeasureModeExactly;
    }

    // The W3C spec doesn't say anything about the 'overflow' property, but all
    // major browsers appear to implement the following logic.
    if ((!isMainAxisRow && node->getStyle().overflow == ABI33_0_0YGOverflowScroll) ||
        node->getStyle().overflow != ABI33_0_0YGOverflowScroll) {
      if (ABI33_0_0YGFloatIsUndefined(childWidth) && !ABI33_0_0YGFloatIsUndefined(width)) {
        childWidth = width;
        childWidthMeasureMode = ABI33_0_0YGMeasureModeAtMost;
      }
    }

    if ((isMainAxisRow && node->getStyle().overflow == ABI33_0_0YGOverflowScroll) ||
        node->getStyle().overflow != ABI33_0_0YGOverflowScroll) {
      if (ABI33_0_0YGFloatIsUndefined(childHeight) && !ABI33_0_0YGFloatIsUndefined(height)) {
        childHeight = height;
        childHeightMeasureMode = ABI33_0_0YGMeasureModeAtMost;
      }
    }

    if (!child->getStyle().aspectRatio.isUndefined()) {
      if (!isMainAxisRow && childWidthMeasureMode == ABI33_0_0YGMeasureModeExactly) {
        childHeight = marginColumn +
            (childWidth - marginRow) / child->getStyle().aspectRatio.unwrap();
        childHeightMeasureMode = ABI33_0_0YGMeasureModeExactly;
      } else if (
          isMainAxisRow && childHeightMeasureMode == ABI33_0_0YGMeasureModeExactly) {
        childWidth = marginRow +
            (childHeight - marginColumn) *
                child->getStyle().aspectRatio.unwrap();
        childWidthMeasureMode = ABI33_0_0YGMeasureModeExactly;
      }
    }

    // If child has no defined size in the cross axis and is set to stretch, set
    // the cross axis to be measured exactly with the available inner width

    const bool hasExactWidth =
        !ABI33_0_0YGFloatIsUndefined(width) && widthMode == ABI33_0_0YGMeasureModeExactly;
    const bool childWidthStretch =
        ABI33_0_0YGNodeAlignItem(node, child) == ABI33_0_0YGAlignStretch &&
        childWidthMeasureMode != ABI33_0_0YGMeasureModeExactly;
    if (!isMainAxisRow && !isRowStyleDimDefined && hasExactWidth &&
        childWidthStretch) {
      childWidth = width;
      childWidthMeasureMode = ABI33_0_0YGMeasureModeExactly;
      if (!child->getStyle().aspectRatio.isUndefined()) {
        childHeight =
            (childWidth - marginRow) / child->getStyle().aspectRatio.unwrap();
        childHeightMeasureMode = ABI33_0_0YGMeasureModeExactly;
      }
    }

    const bool hasExactHeight =
        !ABI33_0_0YGFloatIsUndefined(height) && heightMode == ABI33_0_0YGMeasureModeExactly;
    const bool childHeightStretch =
        ABI33_0_0YGNodeAlignItem(node, child) == ABI33_0_0YGAlignStretch &&
        childHeightMeasureMode != ABI33_0_0YGMeasureModeExactly;
    if (isMainAxisRow && !isColumnStyleDimDefined && hasExactHeight &&
        childHeightStretch) {
      childHeight = height;
      childHeightMeasureMode = ABI33_0_0YGMeasureModeExactly;

      if (!child->getStyle().aspectRatio.isUndefined()) {
        childWidth = (childHeight - marginColumn) *
            child->getStyle().aspectRatio.unwrap();
        childWidthMeasureMode = ABI33_0_0YGMeasureModeExactly;
      }
    }

    ABI33_0_0YGConstrainMaxSizeForMode(
        child,
        ABI33_0_0YGFlexDirectionRow,
        ownerWidth,
        ownerWidth,
        &childWidthMeasureMode,
        &childWidth);
    ABI33_0_0YGConstrainMaxSizeForMode(
        child,
        ABI33_0_0YGFlexDirectionColumn,
        ownerHeight,
        ownerWidth,
        &childHeightMeasureMode,
        &childHeight);

    // Measure the child
    ABI33_0_0YGLayoutNodeInternal(
        child,
        childWidth,
        childHeight,
        direction,
        childWidthMeasureMode,
        childHeightMeasureMode,
        ownerWidth,
        ownerHeight,
        false,
        "measure",
        config,
        layoutMarkerData);

    child->setLayoutComputedFlexBasis(ABI33_0_0YGFloatOptional(ABI33_0_0YGFloatMax(
        child->getLayout().measuredDimensions[dim[mainAxis]],
        ABI33_0_0YGNodePaddingAndBorderForAxis(child, mainAxis, ownerWidth))));
  }
  child->setLayoutComputedFlexBasisGeneration(gCurrentGenerationCount);
}

static void ABI33_0_0YGNodeAbsoluteLayoutChild(
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGNodeRef child,
    const float width,
    const ABI33_0_0YGMeasureMode widthMode,
    const float height,
    const ABI33_0_0YGDirection direction,
    const ABI33_0_0YGConfigRef config,
    ABI33_0_0YGMarkerLayoutData& layoutMarkerData) {
  const ABI33_0_0YGFlexDirection mainAxis =
      ABI33_0_0YGResolveFlexDirection(node->getStyle().flexDirection, direction);
  const ABI33_0_0YGFlexDirection crossAxis = ABI33_0_0YGFlexDirectionCross(mainAxis, direction);
  const bool isMainAxisRow = ABI33_0_0YGFlexDirectionIsRow(mainAxis);

  float childWidth = ABI33_0_0YGUndefined;
  float childHeight = ABI33_0_0YGUndefined;
  ABI33_0_0YGMeasureMode childWidthMeasureMode = ABI33_0_0YGMeasureModeUndefined;
  ABI33_0_0YGMeasureMode childHeightMeasureMode = ABI33_0_0YGMeasureModeUndefined;

  auto marginRow = child->getMarginForAxis(ABI33_0_0YGFlexDirectionRow, width).unwrap();
  auto marginColumn =
      child->getMarginForAxis(ABI33_0_0YGFlexDirectionColumn, width).unwrap();

  if (ABI33_0_0YGNodeIsStyleDimDefined(child, ABI33_0_0YGFlexDirectionRow, width)) {
    childWidth =
        ABI33_0_0YGResolveValue(child->getResolvedDimension(ABI33_0_0YGDimensionWidth), width)
            .unwrap() +
        marginRow;
  } else {
    // If the child doesn't have a specified width, compute the width based on
    // the left/right offsets if they're defined.
    if (child->isLeadingPositionDefined(ABI33_0_0YGFlexDirectionRow) &&
        child->isTrailingPosDefined(ABI33_0_0YGFlexDirectionRow)) {
      childWidth = node->getLayout().measuredDimensions[ABI33_0_0YGDimensionWidth] -
          (node->getLeadingBorder(ABI33_0_0YGFlexDirectionRow) +
           node->getTrailingBorder(ABI33_0_0YGFlexDirectionRow)) -
          (child->getLeadingPosition(ABI33_0_0YGFlexDirectionRow, width) +
           child->getTrailingPosition(ABI33_0_0YGFlexDirectionRow, width))
              .unwrap();
      childWidth =
          ABI33_0_0YGNodeBoundAxis(child, ABI33_0_0YGFlexDirectionRow, childWidth, width, width);
    }
  }

  if (ABI33_0_0YGNodeIsStyleDimDefined(child, ABI33_0_0YGFlexDirectionColumn, height)) {
    childHeight =
        ABI33_0_0YGResolveValue(child->getResolvedDimension(ABI33_0_0YGDimensionHeight), height)
            .unwrap() +
        marginColumn;
  } else {
    // If the child doesn't have a specified height, compute the height based on
    // the top/bottom offsets if they're defined.
    if (child->isLeadingPositionDefined(ABI33_0_0YGFlexDirectionColumn) &&
        child->isTrailingPosDefined(ABI33_0_0YGFlexDirectionColumn)) {
      childHeight = node->getLayout().measuredDimensions[ABI33_0_0YGDimensionHeight] -
          (node->getLeadingBorder(ABI33_0_0YGFlexDirectionColumn) +
           node->getTrailingBorder(ABI33_0_0YGFlexDirectionColumn)) -
          (child->getLeadingPosition(ABI33_0_0YGFlexDirectionColumn, height) +
           child->getTrailingPosition(ABI33_0_0YGFlexDirectionColumn, height))
              .unwrap();
      childHeight = ABI33_0_0YGNodeBoundAxis(
          child, ABI33_0_0YGFlexDirectionColumn, childHeight, height, width);
    }
  }

  // Exactly one dimension needs to be defined for us to be able to do aspect
  // ratio calculation. One dimension being the anchor and the other being
  // flexible.
  if (ABI33_0_0YGFloatIsUndefined(childWidth) ^ ABI33_0_0YGFloatIsUndefined(childHeight)) {
    if (!child->getStyle().aspectRatio.isUndefined()) {
      if (ABI33_0_0YGFloatIsUndefined(childWidth)) {
        childWidth = marginRow +
            (childHeight - marginColumn) *
                child->getStyle().aspectRatio.unwrap();
      } else if (ABI33_0_0YGFloatIsUndefined(childHeight)) {
        childHeight = marginColumn +
            (childWidth - marginRow) / child->getStyle().aspectRatio.unwrap();
      }
    }
  }

  // If we're still missing one or the other dimension, measure the content.
  if (ABI33_0_0YGFloatIsUndefined(childWidth) || ABI33_0_0YGFloatIsUndefined(childHeight)) {
    childWidthMeasureMode = ABI33_0_0YGFloatIsUndefined(childWidth)
        ? ABI33_0_0YGMeasureModeUndefined
        : ABI33_0_0YGMeasureModeExactly;
    childHeightMeasureMode = ABI33_0_0YGFloatIsUndefined(childHeight)
        ? ABI33_0_0YGMeasureModeUndefined
        : ABI33_0_0YGMeasureModeExactly;

    // If the size of the owner is defined then try to constrain the absolute
    // child to that size as well. This allows text within the absolute child to
    // wrap to the size of its owner. This is the same behavior as many browsers
    // implement.
    if (!isMainAxisRow && ABI33_0_0YGFloatIsUndefined(childWidth) &&
        widthMode != ABI33_0_0YGMeasureModeUndefined && !ABI33_0_0YGFloatIsUndefined(width) &&
        width > 0) {
      childWidth = width;
      childWidthMeasureMode = ABI33_0_0YGMeasureModeAtMost;
    }

    ABI33_0_0YGLayoutNodeInternal(
        child,
        childWidth,
        childHeight,
        direction,
        childWidthMeasureMode,
        childHeightMeasureMode,
        childWidth,
        childHeight,
        false,
        "abs-measure",
        config,
        layoutMarkerData);
    childWidth = child->getLayout().measuredDimensions[ABI33_0_0YGDimensionWidth] +
        child->getMarginForAxis(ABI33_0_0YGFlexDirectionRow, width).unwrap();
    childHeight = child->getLayout().measuredDimensions[ABI33_0_0YGDimensionHeight] +
        child->getMarginForAxis(ABI33_0_0YGFlexDirectionColumn, width).unwrap();
  }

  ABI33_0_0YGLayoutNodeInternal(
      child,
      childWidth,
      childHeight,
      direction,
      ABI33_0_0YGMeasureModeExactly,
      ABI33_0_0YGMeasureModeExactly,
      childWidth,
      childHeight,
      true,
      "abs-layout",
      config,
      layoutMarkerData);

  if (child->isTrailingPosDefined(mainAxis) &&
      !child->isLeadingPositionDefined(mainAxis)) {
    child->setLayoutPosition(
        node->getLayout().measuredDimensions[dim[mainAxis]] -
            child->getLayout().measuredDimensions[dim[mainAxis]] -
            node->getTrailingBorder(mainAxis) -
            child->getTrailingMargin(mainAxis, width).unwrap() -
            child->getTrailingPosition(mainAxis, isMainAxisRow ? width : height)
                .unwrap(),
        leading[mainAxis]);
  } else if (
      !child->isLeadingPositionDefined(mainAxis) &&
      node->getStyle().justifyContent == ABI33_0_0YGJustifyCenter) {
    child->setLayoutPosition(
        (node->getLayout().measuredDimensions[dim[mainAxis]] -
         child->getLayout().measuredDimensions[dim[mainAxis]]) /
            2.0f,
        leading[mainAxis]);
  } else if (
      !child->isLeadingPositionDefined(mainAxis) &&
      node->getStyle().justifyContent == ABI33_0_0YGJustifyFlexEnd) {
    child->setLayoutPosition(
        (node->getLayout().measuredDimensions[dim[mainAxis]] -
         child->getLayout().measuredDimensions[dim[mainAxis]]),
        leading[mainAxis]);
  }

  if (child->isTrailingPosDefined(crossAxis) &&
      !child->isLeadingPositionDefined(crossAxis)) {
    child->setLayoutPosition(
        node->getLayout().measuredDimensions[dim[crossAxis]] -
            child->getLayout().measuredDimensions[dim[crossAxis]] -
            node->getTrailingBorder(crossAxis) -
            child->getTrailingMargin(crossAxis, width).unwrap() -
            child
                ->getTrailingPosition(crossAxis, isMainAxisRow ? height : width)
                .unwrap(),
        leading[crossAxis]);

  } else if (
      !child->isLeadingPositionDefined(crossAxis) &&
      ABI33_0_0YGNodeAlignItem(node, child) == ABI33_0_0YGAlignCenter) {
    child->setLayoutPosition(
        (node->getLayout().measuredDimensions[dim[crossAxis]] -
         child->getLayout().measuredDimensions[dim[crossAxis]]) /
            2.0f,
        leading[crossAxis]);
  } else if (
      !child->isLeadingPositionDefined(crossAxis) &&
      ((ABI33_0_0YGNodeAlignItem(node, child) == ABI33_0_0YGAlignFlexEnd) ^
       (node->getStyle().flexWrap == ABI33_0_0YGWrapWrapReverse))) {
    child->setLayoutPosition(
        (node->getLayout().measuredDimensions[dim[crossAxis]] -
         child->getLayout().measuredDimensions[dim[crossAxis]]),
        leading[crossAxis]);
  }
}

static void ABI33_0_0YGNodeWithMeasureFuncSetMeasuredDimensions(
    const ABI33_0_0YGNodeRef node,
    const float availableWidth,
    const float availableHeight,
    const ABI33_0_0YGMeasureMode widthMeasureMode,
    const ABI33_0_0YGMeasureMode heightMeasureMode,
    const float ownerWidth,
    const float ownerHeight) {
  ABI33_0_0YGAssertWithNode(
      node,
      node->getMeasure() != nullptr,
      "Expected node to have custom measure function");

  const float paddingAndBorderAxisRow =
      ABI33_0_0YGNodePaddingAndBorderForAxis(node, ABI33_0_0YGFlexDirectionRow, availableWidth);
  const float paddingAndBorderAxisColumn = ABI33_0_0YGNodePaddingAndBorderForAxis(
      node, ABI33_0_0YGFlexDirectionColumn, availableWidth);
  const float marginAxisRow =
      node->getMarginForAxis(ABI33_0_0YGFlexDirectionRow, availableWidth).unwrap();
  const float marginAxisColumn =
      node->getMarginForAxis(ABI33_0_0YGFlexDirectionColumn, availableWidth).unwrap();

  // We want to make sure we don't call measure with negative size
  const float innerWidth = ABI33_0_0YGFloatIsUndefined(availableWidth)
      ? availableWidth
      : ABI33_0_0YGFloatMax(0, availableWidth - marginAxisRow - paddingAndBorderAxisRow);
  const float innerHeight = ABI33_0_0YGFloatIsUndefined(availableHeight)
      ? availableHeight
      : ABI33_0_0YGFloatMax(
            0, availableHeight - marginAxisColumn - paddingAndBorderAxisColumn);

  if (widthMeasureMode == ABI33_0_0YGMeasureModeExactly &&
      heightMeasureMode == ABI33_0_0YGMeasureModeExactly) {
    // Don't bother sizing the text if both dimensions are already defined.
    node->setLayoutMeasuredDimension(
        ABI33_0_0YGNodeBoundAxis(
            node,
            ABI33_0_0YGFlexDirectionRow,
            availableWidth - marginAxisRow,
            ownerWidth,
            ownerWidth),
        ABI33_0_0YGDimensionWidth);
    node->setLayoutMeasuredDimension(
        ABI33_0_0YGNodeBoundAxis(
            node,
            ABI33_0_0YGFlexDirectionColumn,
            availableHeight - marginAxisColumn,
            ownerHeight,
            ownerWidth),
        ABI33_0_0YGDimensionHeight);
  } else {
    // Measure the text under the current constraints.
    const ABI33_0_0YGSize measuredSize = marker::MarkerSection<ABI33_0_0YGMarkerMeasure>::wrap(
        node,
        node->getMeasure(),
        node,
        innerWidth,
        widthMeasureMode,
        innerHeight,
        heightMeasureMode);

    node->setLayoutMeasuredDimension(
        ABI33_0_0YGNodeBoundAxis(
            node,
            ABI33_0_0YGFlexDirectionRow,
            (widthMeasureMode == ABI33_0_0YGMeasureModeUndefined ||
             widthMeasureMode == ABI33_0_0YGMeasureModeAtMost)
                ? measuredSize.width + paddingAndBorderAxisRow
                : availableWidth - marginAxisRow,
            ownerWidth,
            ownerWidth),
        ABI33_0_0YGDimensionWidth);

    node->setLayoutMeasuredDimension(
        ABI33_0_0YGNodeBoundAxis(
            node,
            ABI33_0_0YGFlexDirectionColumn,
            (heightMeasureMode == ABI33_0_0YGMeasureModeUndefined ||
             heightMeasureMode == ABI33_0_0YGMeasureModeAtMost)
                ? measuredSize.height + paddingAndBorderAxisColumn
                : availableHeight - marginAxisColumn,
            ownerHeight,
            ownerWidth),
        ABI33_0_0YGDimensionHeight);
  }
}

// For nodes with no children, use the available values if they were provided,
// or the minimum size as indicated by the padding and border sizes.
static void ABI33_0_0YGNodeEmptyContainerSetMeasuredDimensions(
    const ABI33_0_0YGNodeRef node,
    const float availableWidth,
    const float availableHeight,
    const ABI33_0_0YGMeasureMode widthMeasureMode,
    const ABI33_0_0YGMeasureMode heightMeasureMode,
    const float ownerWidth,
    const float ownerHeight) {
  const float paddingAndBorderAxisRow =
      ABI33_0_0YGNodePaddingAndBorderForAxis(node, ABI33_0_0YGFlexDirectionRow, ownerWidth);
  const float paddingAndBorderAxisColumn =
      ABI33_0_0YGNodePaddingAndBorderForAxis(node, ABI33_0_0YGFlexDirectionColumn, ownerWidth);
  const float marginAxisRow =
      node->getMarginForAxis(ABI33_0_0YGFlexDirectionRow, ownerWidth).unwrap();
  const float marginAxisColumn =
      node->getMarginForAxis(ABI33_0_0YGFlexDirectionColumn, ownerWidth).unwrap();

  node->setLayoutMeasuredDimension(
      ABI33_0_0YGNodeBoundAxis(
          node,
          ABI33_0_0YGFlexDirectionRow,
          (widthMeasureMode == ABI33_0_0YGMeasureModeUndefined ||
           widthMeasureMode == ABI33_0_0YGMeasureModeAtMost)
              ? paddingAndBorderAxisRow
              : availableWidth - marginAxisRow,
          ownerWidth,
          ownerWidth),
      ABI33_0_0YGDimensionWidth);

  node->setLayoutMeasuredDimension(
      ABI33_0_0YGNodeBoundAxis(
          node,
          ABI33_0_0YGFlexDirectionColumn,
          (heightMeasureMode == ABI33_0_0YGMeasureModeUndefined ||
           heightMeasureMode == ABI33_0_0YGMeasureModeAtMost)
              ? paddingAndBorderAxisColumn
              : availableHeight - marginAxisColumn,
          ownerHeight,
          ownerWidth),
      ABI33_0_0YGDimensionHeight);
}

static bool ABI33_0_0YGNodeFixedSizeSetMeasuredDimensions(
    const ABI33_0_0YGNodeRef node,
    const float availableWidth,
    const float availableHeight,
    const ABI33_0_0YGMeasureMode widthMeasureMode,
    const ABI33_0_0YGMeasureMode heightMeasureMode,
    const float ownerWidth,
    const float ownerHeight) {
  if ((!ABI33_0_0YGFloatIsUndefined(availableWidth) &&
       widthMeasureMode == ABI33_0_0YGMeasureModeAtMost && availableWidth <= 0.0f) ||
      (!ABI33_0_0YGFloatIsUndefined(availableHeight) &&
       heightMeasureMode == ABI33_0_0YGMeasureModeAtMost && availableHeight <= 0.0f) ||
      (widthMeasureMode == ABI33_0_0YGMeasureModeExactly &&
       heightMeasureMode == ABI33_0_0YGMeasureModeExactly)) {
    auto marginAxisColumn =
        node->getMarginForAxis(ABI33_0_0YGFlexDirectionColumn, ownerWidth).unwrap();
    auto marginAxisRow =
        node->getMarginForAxis(ABI33_0_0YGFlexDirectionRow, ownerWidth).unwrap();

    node->setLayoutMeasuredDimension(
        ABI33_0_0YGNodeBoundAxis(
            node,
            ABI33_0_0YGFlexDirectionRow,
            ABI33_0_0YGFloatIsUndefined(availableWidth) ||
                    (widthMeasureMode == ABI33_0_0YGMeasureModeAtMost &&
                     availableWidth < 0.0f)
                ? 0.0f
                : availableWidth - marginAxisRow,
            ownerWidth,
            ownerWidth),
        ABI33_0_0YGDimensionWidth);

    node->setLayoutMeasuredDimension(
        ABI33_0_0YGNodeBoundAxis(
            node,
            ABI33_0_0YGFlexDirectionColumn,
            ABI33_0_0YGFloatIsUndefined(availableHeight) ||
                    (heightMeasureMode == ABI33_0_0YGMeasureModeAtMost &&
                     availableHeight < 0.0f)
                ? 0.0f
                : availableHeight - marginAxisColumn,
            ownerHeight,
            ownerWidth),
        ABI33_0_0YGDimensionHeight);
    return true;
  }

  return false;
}

static void ABI33_0_0YGZeroOutLayoutRecursivly(const ABI33_0_0YGNodeRef node) {
  node->getLayout() = {};
  node->setLayoutDimension(0, 0);
  node->setLayoutDimension(0, 1);
  node->setHasNewLayout(true);
  node->cloneChildrenIfNeeded();
  const uint32_t childCount = ABI33_0_0YGNodeGetChildCount(node);
  for (uint32_t i = 0; i < childCount; i++) {
    const ABI33_0_0YGNodeRef child = node->getChild(i);
    ABI33_0_0YGZeroOutLayoutRecursivly(child);
  }
}

static float ABI33_0_0YGNodeCalculateAvailableInnerDim(
    const ABI33_0_0YGNodeRef node,
    ABI33_0_0YGFlexDirection axis,
    float availableDim,
    float ownerDim) {
  ABI33_0_0YGFlexDirection direction =
      ABI33_0_0YGFlexDirectionIsRow(axis) ? ABI33_0_0YGFlexDirectionRow : ABI33_0_0YGFlexDirectionColumn;
  ABI33_0_0YGDimension dimension =
      ABI33_0_0YGFlexDirectionIsRow(axis) ? ABI33_0_0YGDimensionWidth : ABI33_0_0YGDimensionHeight;

  const float margin = node->getMarginForAxis(direction, ownerDim).unwrap();
  const float paddingAndBorder =
      ABI33_0_0YGNodePaddingAndBorderForAxis(node, direction, ownerDim);

  float availableInnerDim = availableDim - margin - paddingAndBorder;
  // Max dimension overrides predefined dimension value; Min dimension in turn
  // overrides both of the above
  if (!ABI33_0_0YGFloatIsUndefined(availableInnerDim)) {
    // We want to make sure our available height does not violate min and max
    // constraints
    const ABI33_0_0YGFloatOptional minDimensionOptional =
        ABI33_0_0YGResolveValue(node->getStyle().minDimensions[dimension], ownerDim);
    const float minInnerDim = minDimensionOptional.isUndefined()
        ? 0.0f
        : minDimensionOptional.unwrap() - paddingAndBorder;

    const ABI33_0_0YGFloatOptional maxDimensionOptional =
        ABI33_0_0YGResolveValue(node->getStyle().maxDimensions[dimension], ownerDim);

    const float maxInnerDim = maxDimensionOptional.isUndefined()
        ? FLT_MAX
        : maxDimensionOptional.unwrap() - paddingAndBorder;
    availableInnerDim =
        ABI33_0_0YGFloatMax(ABI33_0_0YGFloatMin(availableInnerDim, maxInnerDim), minInnerDim);
  }

  return availableInnerDim;
}

static float ABI33_0_0YGNodeComputeFlexBasisForChildren(
    const ABI33_0_0YGNodeRef node,
    const float availableInnerWidth,
    const float availableInnerHeight,
    ABI33_0_0YGMeasureMode widthMeasureMode,
    ABI33_0_0YGMeasureMode heightMeasureMode,
    ABI33_0_0YGDirection direction,
    ABI33_0_0YGFlexDirection mainAxis,
    const ABI33_0_0YGConfigRef config,
    bool performLayout,
    ABI33_0_0YGMarkerLayoutData& layoutMarkerData) {
  float totalOuterFlexBasis = 0.0f;
  ABI33_0_0YGNodeRef singleFlexChild = nullptr;
  ABI33_0_0YGVector children = node->getChildren();
  ABI33_0_0YGMeasureMode measureModeMainDim =
      ABI33_0_0YGFlexDirectionIsRow(mainAxis) ? widthMeasureMode : heightMeasureMode;
  // If there is only one child with flexGrow + flexShrink it means we can set
  // the computedFlexBasis to 0 instead of measuring and shrinking / flexing the
  // child to exactly match the remaining space
  if (measureModeMainDim == ABI33_0_0YGMeasureModeExactly) {
    for (auto child : children) {
      if (child->isNodeFlexible()) {
        if (singleFlexChild != nullptr ||
            ABI33_0_0YGFloatsEqual(child->resolveFlexGrow(), 0.0f) ||
            ABI33_0_0YGFloatsEqual(child->resolveFlexShrink(), 0.0f)) {
          // There is already a flexible child, or this flexible child doesn't
          // have flexGrow and flexShrink, abort
          singleFlexChild = nullptr;
          break;
        } else {
          singleFlexChild = child;
        }
      }
    }
  }

  for (auto child : children) {
    child->resolveDimension();
    if (child->getStyle().display == ABI33_0_0YGDisplayNone) {
      ABI33_0_0YGZeroOutLayoutRecursivly(child);
      child->setHasNewLayout(true);
      child->setDirty(false);
      continue;
    }
    if (performLayout) {
      // Set the initial position (relative to the owner).
      const ABI33_0_0YGDirection childDirection = child->resolveDirection(direction);
      const float mainDim = ABI33_0_0YGFlexDirectionIsRow(mainAxis)
          ? availableInnerWidth
          : availableInnerHeight;
      const float crossDim = ABI33_0_0YGFlexDirectionIsRow(mainAxis)
          ? availableInnerHeight
          : availableInnerWidth;
      child->setPosition(
          childDirection, mainDim, crossDim, availableInnerWidth);
    }

    if (child->getStyle().positionType == ABI33_0_0YGPositionTypeAbsolute) {
      continue;
    }
    if (child == singleFlexChild) {
      child->setLayoutComputedFlexBasisGeneration(gCurrentGenerationCount);
      child->setLayoutComputedFlexBasis(ABI33_0_0YGFloatOptional(0));
    } else {
      ABI33_0_0YGNodeComputeFlexBasisForChild(
          node,
          child,
          availableInnerWidth,
          widthMeasureMode,
          availableInnerHeight,
          availableInnerWidth,
          availableInnerHeight,
          heightMeasureMode,
          direction,
          config,
          layoutMarkerData);
    }

    totalOuterFlexBasis +=
        (child->getLayout().computedFlexBasis +
         child->getMarginForAxis(mainAxis, availableInnerWidth))
            .unwrap();
  }

  return totalOuterFlexBasis;
}

// This function assumes that all the children of node have their
// computedFlexBasis properly computed(To do this use
// ABI33_0_0YGNodeComputeFlexBasisForChildren function). This function calculates
// ABI33_0_0YGCollectFlexItemsRowMeasurement
static ABI33_0_0YGCollectFlexItemsRowValues ABI33_0_0YGCalculateCollectFlexItemsRowValues(
    const ABI33_0_0YGNodeRef& node,
    const ABI33_0_0YGDirection ownerDirection,
    const float mainAxisownerSize,
    const float availableInnerWidth,
    const float availableInnerMainDim,
    const uint32_t startOfLineIndex,
    const uint32_t lineCount) {
  ABI33_0_0YGCollectFlexItemsRowValues flexAlgoRowMeasurement = {};
  flexAlgoRowMeasurement.relativeChildren.reserve(node->getChildren().size());

  float sizeConsumedOnCurrentLineIncludingMinConstraint = 0;
  const ABI33_0_0YGFlexDirection mainAxis = ABI33_0_0YGResolveFlexDirection(
      node->getStyle().flexDirection, node->resolveDirection(ownerDirection));
  const bool isNodeFlexWrap = node->getStyle().flexWrap != ABI33_0_0YGWrapNoWrap;

  // Add items to the current line until it's full or we run out of items.
  uint32_t endOfLineIndex = startOfLineIndex;
  for (; endOfLineIndex < node->getChildren().size(); endOfLineIndex++) {
    const ABI33_0_0YGNodeRef child = node->getChild(endOfLineIndex);
    if (child->getStyle().display == ABI33_0_0YGDisplayNone ||
        child->getStyle().positionType == ABI33_0_0YGPositionTypeAbsolute) {
      continue;
    }
    child->setLineIndex(lineCount);
    const float childMarginMainAxis =
        child->getMarginForAxis(mainAxis, availableInnerWidth).unwrap();
    const float flexBasisWithMinAndMaxConstraints =
        ABI33_0_0YGNodeBoundAxisWithinMinAndMax(
            child,
            mainAxis,
            child->getLayout().computedFlexBasis,
            mainAxisownerSize)
            .unwrap();

    // If this is a multi-line flow and this item pushes us over the available
    // size, we've hit the end of the current line. Break out of the loop and
    // lay out the current line.
    if (sizeConsumedOnCurrentLineIncludingMinConstraint +
                flexBasisWithMinAndMaxConstraints + childMarginMainAxis >
            availableInnerMainDim &&
        isNodeFlexWrap && flexAlgoRowMeasurement.itemsOnLine > 0) {
      break;
    }

    sizeConsumedOnCurrentLineIncludingMinConstraint +=
        flexBasisWithMinAndMaxConstraints + childMarginMainAxis;
    flexAlgoRowMeasurement.sizeConsumedOnCurrentLine +=
        flexBasisWithMinAndMaxConstraints + childMarginMainAxis;
    flexAlgoRowMeasurement.itemsOnLine++;

    if (child->isNodeFlexible()) {
      flexAlgoRowMeasurement.totalFlexGrowFactors += child->resolveFlexGrow();

      // Unlike the grow factor, the shrink factor is scaled relative to the
      // child dimension.
      flexAlgoRowMeasurement.totalFlexShrinkScaledFactors +=
          -child->resolveFlexShrink() *
          child->getLayout().computedFlexBasis.unwrap();
    }

    flexAlgoRowMeasurement.relativeChildren.push_back(child);
  }

  // The total flex factor needs to be floored to 1.
  if (flexAlgoRowMeasurement.totalFlexGrowFactors > 0 &&
      flexAlgoRowMeasurement.totalFlexGrowFactors < 1) {
    flexAlgoRowMeasurement.totalFlexGrowFactors = 1;
  }

  // The total flex shrink factor needs to be floored to 1.
  if (flexAlgoRowMeasurement.totalFlexShrinkScaledFactors > 0 &&
      flexAlgoRowMeasurement.totalFlexShrinkScaledFactors < 1) {
    flexAlgoRowMeasurement.totalFlexShrinkScaledFactors = 1;
  }
  flexAlgoRowMeasurement.endOfLineIndex = endOfLineIndex;
  return flexAlgoRowMeasurement;
}

// It distributes the free space to the flexible items and ensures that the size
// of the flex items abide the min and max constraints. At the end of this
// function the child nodes would have proper size. Prior using this function
// please ensure that ABI33_0_0YGDistributeFreeSpaceFirstPass is called.
static float ABI33_0_0YGDistributeFreeSpaceSecondPass(
    ABI33_0_0YGCollectFlexItemsRowValues& collectedFlexItemsValues,
    const ABI33_0_0YGNodeRef node,
    const ABI33_0_0YGFlexDirection mainAxis,
    const ABI33_0_0YGFlexDirection crossAxis,
    const float mainAxisownerSize,
    const float availableInnerMainDim,
    const float availableInnerCrossDim,
    const float availableInnerWidth,
    const float availableInnerHeight,
    const bool flexBasisOverflows,
    const ABI33_0_0YGMeasureMode measureModeCrossDim,
    const bool performLayout,
    const ABI33_0_0YGConfigRef config,
    ABI33_0_0YGMarkerLayoutData& layoutMarkerData) {
  float childFlexBasis = 0;
  float flexShrinkScaledFactor = 0;
  float flexGrowFactor = 0;
  float deltaFreeSpace = 0;
  const bool isMainAxisRow = ABI33_0_0YGFlexDirectionIsRow(mainAxis);
  const bool isNodeFlexWrap = node->getStyle().flexWrap != ABI33_0_0YGWrapNoWrap;

  for (auto currentRelativeChild : collectedFlexItemsValues.relativeChildren) {
    childFlexBasis = ABI33_0_0YGNodeBoundAxisWithinMinAndMax(
                         currentRelativeChild,
                         mainAxis,
                         currentRelativeChild->getLayout().computedFlexBasis,
                         mainAxisownerSize)
                         .unwrap();
    float updatedMainSize = childFlexBasis;

    if (!ABI33_0_0YGFloatIsUndefined(collectedFlexItemsValues.remainingFreeSpace) &&
        collectedFlexItemsValues.remainingFreeSpace < 0) {
      flexShrinkScaledFactor =
          -currentRelativeChild->resolveFlexShrink() * childFlexBasis;
      // Is this child able to shrink?
      if (flexShrinkScaledFactor != 0) {
        float childSize;

        if (!ABI33_0_0YGFloatIsUndefined(
                collectedFlexItemsValues.totalFlexShrinkScaledFactors) &&
            collectedFlexItemsValues.totalFlexShrinkScaledFactors == 0) {
          childSize = childFlexBasis + flexShrinkScaledFactor;
        } else {
          childSize = childFlexBasis +
              (collectedFlexItemsValues.remainingFreeSpace /
               collectedFlexItemsValues.totalFlexShrinkScaledFactors) *
                  flexShrinkScaledFactor;
        }

        updatedMainSize = ABI33_0_0YGNodeBoundAxis(
            currentRelativeChild,
            mainAxis,
            childSize,
            availableInnerMainDim,
            availableInnerWidth);
      }
    } else if (
        !ABI33_0_0YGFloatIsUndefined(collectedFlexItemsValues.remainingFreeSpace) &&
        collectedFlexItemsValues.remainingFreeSpace > 0) {
      flexGrowFactor = currentRelativeChild->resolveFlexGrow();

      // Is this child able to grow?
      if (!ABI33_0_0YGFloatIsUndefined(flexGrowFactor) && flexGrowFactor != 0) {
        updatedMainSize = ABI33_0_0YGNodeBoundAxis(
            currentRelativeChild,
            mainAxis,
            childFlexBasis +
                collectedFlexItemsValues.remainingFreeSpace /
                    collectedFlexItemsValues.totalFlexGrowFactors *
                    flexGrowFactor,
            availableInnerMainDim,
            availableInnerWidth);
      }
    }

    deltaFreeSpace += updatedMainSize - childFlexBasis;

    const float marginMain =
        currentRelativeChild->getMarginForAxis(mainAxis, availableInnerWidth)
            .unwrap();
    const float marginCross =
        currentRelativeChild->getMarginForAxis(crossAxis, availableInnerWidth)
            .unwrap();

    float childCrossSize;
    float childMainSize = updatedMainSize + marginMain;
    ABI33_0_0YGMeasureMode childCrossMeasureMode;
    ABI33_0_0YGMeasureMode childMainMeasureMode = ABI33_0_0YGMeasureModeExactly;

    if (!currentRelativeChild->getStyle().aspectRatio.isUndefined()) {
      childCrossSize = isMainAxisRow ? (childMainSize - marginMain) /
              currentRelativeChild->getStyle().aspectRatio.unwrap()
                                     : (childMainSize - marginMain) *
              currentRelativeChild->getStyle().aspectRatio.unwrap();
      childCrossMeasureMode = ABI33_0_0YGMeasureModeExactly;

      childCrossSize += marginCross;
    } else if (
        !ABI33_0_0YGFloatIsUndefined(availableInnerCrossDim) &&
        !ABI33_0_0YGNodeIsStyleDimDefined(
            currentRelativeChild, crossAxis, availableInnerCrossDim) &&
        measureModeCrossDim == ABI33_0_0YGMeasureModeExactly &&
        !(isNodeFlexWrap && flexBasisOverflows) &&
        ABI33_0_0YGNodeAlignItem(node, currentRelativeChild) == ABI33_0_0YGAlignStretch &&
        currentRelativeChild->marginLeadingValue(crossAxis).unit !=
            ABI33_0_0YGUnitAuto &&
        currentRelativeChild->marginTrailingValue(crossAxis).unit !=
            ABI33_0_0YGUnitAuto) {
      childCrossSize = availableInnerCrossDim;
      childCrossMeasureMode = ABI33_0_0YGMeasureModeExactly;
    } else if (!ABI33_0_0YGNodeIsStyleDimDefined(
                   currentRelativeChild, crossAxis, availableInnerCrossDim)) {
      childCrossSize = availableInnerCrossDim;
      childCrossMeasureMode = ABI33_0_0YGFloatIsUndefined(childCrossSize)
          ? ABI33_0_0YGMeasureModeUndefined
          : ABI33_0_0YGMeasureModeAtMost;
    } else {
      childCrossSize =
          ABI33_0_0YGResolveValue(
              currentRelativeChild->getResolvedDimension(dim[crossAxis]),
              availableInnerCrossDim)
              .unwrap() +
          marginCross;
      const bool isLoosePercentageMeasurement =
          currentRelativeChild->getResolvedDimension(dim[crossAxis]).unit ==
              ABI33_0_0YGUnitPercent &&
          measureModeCrossDim != ABI33_0_0YGMeasureModeExactly;
      childCrossMeasureMode =
          ABI33_0_0YGFloatIsUndefined(childCrossSize) || isLoosePercentageMeasurement
          ? ABI33_0_0YGMeasureModeUndefined
          : ABI33_0_0YGMeasureModeExactly;
    }

    ABI33_0_0YGConstrainMaxSizeForMode(
        currentRelativeChild,
        mainAxis,
        availableInnerMainDim,
        availableInnerWidth,
        &childMainMeasureMode,
        &childMainSize);
    ABI33_0_0YGConstrainMaxSizeForMode(
        currentRelativeChild,
        crossAxis,
        availableInnerCrossDim,
        availableInnerWidth,
        &childCrossMeasureMode,
        &childCrossSize);

    const bool requiresStretchLayout =
        !ABI33_0_0YGNodeIsStyleDimDefined(
            currentRelativeChild, crossAxis, availableInnerCrossDim) &&
        ABI33_0_0YGNodeAlignItem(node, currentRelativeChild) == ABI33_0_0YGAlignStretch &&
        currentRelativeChild->marginLeadingValue(crossAxis).unit !=
            ABI33_0_0YGUnitAuto &&
        currentRelativeChild->marginTrailingValue(crossAxis).unit != ABI33_0_0YGUnitAuto;

    const float childWidth = isMainAxisRow ? childMainSize : childCrossSize;
    const float childHeight = !isMainAxisRow ? childMainSize : childCrossSize;

    const ABI33_0_0YGMeasureMode childWidthMeasureMode =
        isMainAxisRow ? childMainMeasureMode : childCrossMeasureMode;
    const ABI33_0_0YGMeasureMode childHeightMeasureMode =
        !isMainAxisRow ? childMainMeasureMode : childCrossMeasureMode;

    // Recursively call the layout algorithm for this child with the updated
    // main size.
    ABI33_0_0YGLayoutNodeInternal(
        currentRelativeChild,
        childWidth,
        childHeight,
        node->getLayout().direction,
        childWidthMeasureMode,
        childHeightMeasureMode,
        availableInnerWidth,
        availableInnerHeight,
        performLayout && !requiresStretchLayout,
        "flex",
        config,
        layoutMarkerData);
    node->setLayoutHadOverflow(
        node->getLayout().hadOverflow |
        currentRelativeChild->getLayout().hadOverflow);
  }
  return deltaFreeSpace;
}

// It distributes the free space to the flexible items.For those flexible items
// whose min and max constraints are triggered, those flex item's clamped size
// is removed from the remaingfreespace.
static void ABI33_0_0YGDistributeFreeSpaceFirstPass(
    ABI33_0_0YGCollectFlexItemsRowValues& collectedFlexItemsValues,
    const ABI33_0_0YGFlexDirection mainAxis,
    const float mainAxisownerSize,
    const float availableInnerMainDim,
    const float availableInnerWidth) {
  float flexShrinkScaledFactor = 0;
  float flexGrowFactor = 0;
  float baseMainSize = 0;
  float boundMainSize = 0;
  float deltaFreeSpace = 0;

  for (auto currentRelativeChild : collectedFlexItemsValues.relativeChildren) {
    float childFlexBasis =
        ABI33_0_0YGNodeBoundAxisWithinMinAndMax(
            currentRelativeChild,
            mainAxis,
            currentRelativeChild->getLayout().computedFlexBasis,
            mainAxisownerSize)
            .unwrap();

    if (collectedFlexItemsValues.remainingFreeSpace < 0) {
      flexShrinkScaledFactor =
          -currentRelativeChild->resolveFlexShrink() * childFlexBasis;

      // Is this child able to shrink?
      if (!ABI33_0_0YGFloatIsUndefined(flexShrinkScaledFactor) &&
          flexShrinkScaledFactor != 0) {
        baseMainSize = childFlexBasis +
            collectedFlexItemsValues.remainingFreeSpace /
                collectedFlexItemsValues.totalFlexShrinkScaledFactors *
                flexShrinkScaledFactor;
        boundMainSize = ABI33_0_0YGNodeBoundAxis(
            currentRelativeChild,
            mainAxis,
            baseMainSize,
            availableInnerMainDim,
            availableInnerWidth);
        if (!ABI33_0_0YGFloatIsUndefined(baseMainSize) &&
            !ABI33_0_0YGFloatIsUndefined(boundMainSize) &&
            baseMainSize != boundMainSize) {
          // By excluding this item's size and flex factor from remaining, this
          // item's min/max constraints should also trigger in the second pass
          // resulting in the item's size calculation being identical in the
          // first and second passes.
          deltaFreeSpace += boundMainSize - childFlexBasis;
          collectedFlexItemsValues.totalFlexShrinkScaledFactors -=
              flexShrinkScaledFactor;
        }
      }
    } else if (
        !ABI33_0_0YGFloatIsUndefined(collectedFlexItemsValues.remainingFreeSpace) &&
        collectedFlexItemsValues.remainingFreeSpace > 0) {
      flexGrowFactor = currentRelativeChild->resolveFlexGrow();

      // Is this child able to grow?
      if (!ABI33_0_0YGFloatIsUndefined(flexGrowFactor) && flexGrowFactor != 0) {
        baseMainSize = childFlexBasis +
            collectedFlexItemsValues.remainingFreeSpace /
                collectedFlexItemsValues.totalFlexGrowFactors * flexGrowFactor;
        boundMainSize = ABI33_0_0YGNodeBoundAxis(
            currentRelativeChild,
            mainAxis,
            baseMainSize,
            availableInnerMainDim,
            availableInnerWidth);

        if (!ABI33_0_0YGFloatIsUndefined(baseMainSize) &&
            !ABI33_0_0YGFloatIsUndefined(boundMainSize) &&
            baseMainSize != boundMainSize) {
          // By excluding this item's size and flex factor from remaining, this
          // item's min/max constraints should also trigger in the second pass
          // resulting in the item's size calculation being identical in the
          // first and second passes.
          deltaFreeSpace += boundMainSize - childFlexBasis;
          collectedFlexItemsValues.totalFlexGrowFactors -= flexGrowFactor;
        }
      }
    }
  }
  collectedFlexItemsValues.remainingFreeSpace -= deltaFreeSpace;
}

// Do two passes over the flex items to figure out how to distribute the
// remaining space.
//
// The first pass finds the items whose min/max constraints trigger, freezes
// them at those sizes, and excludes those sizes from the remaining space.
//
// The second pass sets the size of each flexible item. It distributes the
// remaining space amongst the items whose min/max constraints didn't trigger in
// the first pass. For the other items, it sets their sizes by forcing their
// min/max constraints to trigger again.
//
// This two pass approach for resolving min/max constraints deviates from the
// spec. The spec
// (https://www.w3.org/TR/CSS-flexbox-1/#resolve-flexible-lengths) describes a
// process that needs to be repeated a variable number of times. The algorithm
// implemented here won't handle all cases but it was simpler to implement and
// it mitigates performance concerns because we know exactly how many passes
// it'll do.
//
// At the end of this function the child nodes would have the proper size
// assigned to them.
//
static void ABI33_0_0YGResolveFlexibleLength(
    const ABI33_0_0YGNodeRef node,
    ABI33_0_0YGCollectFlexItemsRowValues& collectedFlexItemsValues,
    const ABI33_0_0YGFlexDirection mainAxis,
    const ABI33_0_0YGFlexDirection crossAxis,
    const float mainAxisownerSize,
    const float availableInnerMainDim,
    const float availableInnerCrossDim,
    const float availableInnerWidth,
    const float availableInnerHeight,
    const bool flexBasisOverflows,
    const ABI33_0_0YGMeasureMode measureModeCrossDim,
    const bool performLayout,
    const ABI33_0_0YGConfigRef config,
    ABI33_0_0YGMarkerLayoutData& layoutMarkerData) {
  const float originalFreeSpace = collectedFlexItemsValues.remainingFreeSpace;
  // First pass: detect the flex items whose min/max constraints trigger
  ABI33_0_0YGDistributeFreeSpaceFirstPass(
      collectedFlexItemsValues,
      mainAxis,
      mainAxisownerSize,
      availableInnerMainDim,
      availableInnerWidth);

  // Second pass: resolve the sizes of the flexible items
  const float distributedFreeSpace = ABI33_0_0YGDistributeFreeSpaceSecondPass(
      collectedFlexItemsValues,
      node,
      mainAxis,
      crossAxis,
      mainAxisownerSize,
      availableInnerMainDim,
      availableInnerCrossDim,
      availableInnerWidth,
      availableInnerHeight,
      flexBasisOverflows,
      measureModeCrossDim,
      performLayout,
      config,
      layoutMarkerData);

  collectedFlexItemsValues.remainingFreeSpace =
      originalFreeSpace - distributedFreeSpace;
}

static void ABI33_0_0YGJustifyMainAxis(
    const ABI33_0_0YGNodeRef node,
    ABI33_0_0YGCollectFlexItemsRowValues& collectedFlexItemsValues,
    const uint32_t startOfLineIndex,
    const ABI33_0_0YGFlexDirection mainAxis,
    const ABI33_0_0YGFlexDirection crossAxis,
    const ABI33_0_0YGMeasureMode measureModeMainDim,
    const ABI33_0_0YGMeasureMode measureModeCrossDim,
    const float mainAxisownerSize,
    const float ownerWidth,
    const float availableInnerMainDim,
    const float availableInnerCrossDim,
    const float availableInnerWidth,
    const bool performLayout) {
  const ABI33_0_0YGStyle& style = node->getStyle();
  const float leadingPaddingAndBorderMain =
      node->getLeadingPaddingAndBorder(mainAxis, ownerWidth).unwrap();
  const float trailingPaddingAndBorderMain =
      node->getTrailingPaddingAndBorder(mainAxis, ownerWidth).unwrap();
  // If we are using "at most" rules in the main axis, make sure that
  // remainingFreeSpace is 0 when min main dimension is not given
  if (measureModeMainDim == ABI33_0_0YGMeasureModeAtMost &&
      collectedFlexItemsValues.remainingFreeSpace > 0) {
    if (!style.minDimensions[dim[mainAxis]].isUndefined() &&
        !ABI33_0_0YGResolveValue(style.minDimensions[dim[mainAxis]], mainAxisownerSize)
             .isUndefined()) {
      // This condition makes sure that if the size of main dimension(after
      // considering child nodes main dim, leading and trailing padding etc)
      // falls below min dimension, then the remainingFreeSpace is reassigned
      // considering the min dimension

      // `minAvailableMainDim` denotes minimum available space in which child
      // can be laid out, it will exclude space consumed by padding and border.
      const float minAvailableMainDim =
          ABI33_0_0YGResolveValue(style.minDimensions[dim[mainAxis]], mainAxisownerSize)
              .unwrap() -
          leadingPaddingAndBorderMain - trailingPaddingAndBorderMain;
      const float occupiedSpaceByChildNodes =
          availableInnerMainDim - collectedFlexItemsValues.remainingFreeSpace;
      collectedFlexItemsValues.remainingFreeSpace =
          ABI33_0_0YGFloatMax(0, minAvailableMainDim - occupiedSpaceByChildNodes);
    } else {
      collectedFlexItemsValues.remainingFreeSpace = 0;
    }
  }

  int numberOfAutoMarginsOnCurrentLine = 0;
  for (uint32_t i = startOfLineIndex;
       i < collectedFlexItemsValues.endOfLineIndex;
       i++) {
    const ABI33_0_0YGNodeRef child = node->getChild(i);
    if (child->getStyle().positionType == ABI33_0_0YGPositionTypeRelative) {
      if (child->marginLeadingValue(mainAxis).unit == ABI33_0_0YGUnitAuto) {
        numberOfAutoMarginsOnCurrentLine++;
      }
      if (child->marginTrailingValue(mainAxis).unit == ABI33_0_0YGUnitAuto) {
        numberOfAutoMarginsOnCurrentLine++;
      }
    }
  }

  // In order to position the elements in the main axis, we have two controls.
  // The space between the beginning and the first element and the space between
  // each two elements.
  float leadingMainDim = 0;
  float betweenMainDim = 0;
  const ABI33_0_0YGJustify justifyContent = node->getStyle().justifyContent;

  if (numberOfAutoMarginsOnCurrentLine == 0) {
    switch (justifyContent) {
      case ABI33_0_0YGJustifyCenter:
        leadingMainDim = collectedFlexItemsValues.remainingFreeSpace / 2;
        break;
      case ABI33_0_0YGJustifyFlexEnd:
        leadingMainDim = collectedFlexItemsValues.remainingFreeSpace;
        break;
      case ABI33_0_0YGJustifySpaceBetween:
        if (collectedFlexItemsValues.itemsOnLine > 1) {
          betweenMainDim =
              ABI33_0_0YGFloatMax(collectedFlexItemsValues.remainingFreeSpace, 0) /
              (collectedFlexItemsValues.itemsOnLine - 1);
        } else {
          betweenMainDim = 0;
        }
        break;
      case ABI33_0_0YGJustifySpaceEvenly:
        // Space is distributed evenly across all elements
        betweenMainDim = collectedFlexItemsValues.remainingFreeSpace /
            (collectedFlexItemsValues.itemsOnLine + 1);
        leadingMainDim = betweenMainDim;
        break;
      case ABI33_0_0YGJustifySpaceAround:
        // Space on the edges is half of the space between elements
        betweenMainDim = collectedFlexItemsValues.remainingFreeSpace /
            collectedFlexItemsValues.itemsOnLine;
        leadingMainDim = betweenMainDim / 2;
        break;
      case ABI33_0_0YGJustifyFlexStart:
        break;
    }
  }

  collectedFlexItemsValues.mainDim =
      leadingPaddingAndBorderMain + leadingMainDim;
  collectedFlexItemsValues.crossDim = 0;

  float maxAscentForCurrentLine = 0;
  float maxDescentForCurrentLine = 0;
  bool isNodeBaselineLayout = ABI33_0_0YGIsBaselineLayout(node);
  for (uint32_t i = startOfLineIndex;
       i < collectedFlexItemsValues.endOfLineIndex;
       i++) {
    const ABI33_0_0YGNodeRef child = node->getChild(i);
    const ABI33_0_0YGStyle& childStyle = child->getStyle();
    const ABI33_0_0YGLayout childLayout = child->getLayout();
    if (childStyle.display == ABI33_0_0YGDisplayNone) {
      continue;
    }
    if (childStyle.positionType == ABI33_0_0YGPositionTypeAbsolute &&
        child->isLeadingPositionDefined(mainAxis)) {
      if (performLayout) {
        // In case the child is position absolute and has left/top being
        // defined, we override the position to whatever the user said (and
        // margin/border).
        child->setLayoutPosition(
            child->getLeadingPosition(mainAxis, availableInnerMainDim)
                    .unwrap() +
                node->getLeadingBorder(mainAxis) +
                child->getLeadingMargin(mainAxis, availableInnerWidth).unwrap(),
            pos[mainAxis]);
      }
    } else {
      // Now that we placed the element, we need to update the variables.
      // We need to do that only for relative elements. Absolute elements do not
      // take part in that phase.
      if (childStyle.positionType == ABI33_0_0YGPositionTypeRelative) {
        if (child->marginLeadingValue(mainAxis).unit == ABI33_0_0YGUnitAuto) {
          collectedFlexItemsValues.mainDim +=
              collectedFlexItemsValues.remainingFreeSpace /
              numberOfAutoMarginsOnCurrentLine;
        }

        if (performLayout) {
          child->setLayoutPosition(
              childLayout.position[pos[mainAxis]] +
                  collectedFlexItemsValues.mainDim,
              pos[mainAxis]);
        }

        if (child->marginTrailingValue(mainAxis).unit == ABI33_0_0YGUnitAuto) {
          collectedFlexItemsValues.mainDim +=
              collectedFlexItemsValues.remainingFreeSpace /
              numberOfAutoMarginsOnCurrentLine;
        }
        bool canSkipFlex =
            !performLayout && measureModeCrossDim == ABI33_0_0YGMeasureModeExactly;
        if (canSkipFlex) {
          // If we skipped the flex step, then we can't rely on the measuredDims
          // because they weren't computed. This means we can't call
          // ABI33_0_0YGNodeDimWithMargin.
          collectedFlexItemsValues.mainDim += betweenMainDim +
              child->getMarginForAxis(mainAxis, availableInnerWidth).unwrap() +
              childLayout.computedFlexBasis.unwrap();
          collectedFlexItemsValues.crossDim = availableInnerCrossDim;
        } else {
          // The main dimension is the sum of all the elements dimension plus
          // the spacing.
          collectedFlexItemsValues.mainDim += betweenMainDim +
              ABI33_0_0YGNodeDimWithMargin(child, mainAxis, availableInnerWidth);

          if (isNodeBaselineLayout) {
            // If the child is baseline aligned then the cross dimension is
            // calculated by adding maxAscent and maxDescent from the baseline.
            const float ascent = ABI33_0_0YGBaseline(child) +
                child
                    ->getLeadingMargin(
                        ABI33_0_0YGFlexDirectionColumn, availableInnerWidth)
                    .unwrap();
            const float descent =
                child->getLayout().measuredDimensions[ABI33_0_0YGDimensionHeight] +
                child
                    ->getMarginForAxis(
                        ABI33_0_0YGFlexDirectionColumn, availableInnerWidth)
                    .unwrap() -
                ascent;

            maxAscentForCurrentLine =
                ABI33_0_0YGFloatMax(maxAscentForCurrentLine, ascent);
            maxDescentForCurrentLine =
                ABI33_0_0YGFloatMax(maxDescentForCurrentLine, descent);
          } else {
            // The cross dimension is the max of the elements dimension since
            // there can only be one element in that cross dimension in the case
            // when the items are not baseline aligned
            collectedFlexItemsValues.crossDim = ABI33_0_0YGFloatMax(
                collectedFlexItemsValues.crossDim,
                ABI33_0_0YGNodeDimWithMargin(child, crossAxis, availableInnerWidth));
          }
        }
      } else if (performLayout) {
        child->setLayoutPosition(
            childLayout.position[pos[mainAxis]] +
                node->getLeadingBorder(mainAxis) + leadingMainDim,
            pos[mainAxis]);
      }
    }
  }
  collectedFlexItemsValues.mainDim += trailingPaddingAndBorderMain;

  if (isNodeBaselineLayout) {
    collectedFlexItemsValues.crossDim =
        maxAscentForCurrentLine + maxDescentForCurrentLine;
  }
}

//
// This is the main routine that implements a subset of the flexbox layout
// algorithm described in the W3C CSS documentation:
// https://www.w3.org/TR/CSS3-flexbox/.
//
// Limitations of this algorithm, compared to the full standard:
//  * Display property is always assumed to be 'flex' except for Text nodes,
//    which are assumed to be 'inline-flex'.
//  * The 'zIndex' property (or any form of z ordering) is not supported. Nodes
//    are stacked in document order.
//  * The 'order' property is not supported. The order of flex items is always
//    defined by document order.
//  * The 'visibility' property is always assumed to be 'visible'. Values of
//    'collapse' and 'hidden' are not supported.
//  * There is no support for forced breaks.
//  * It does not support vertical inline directions (top-to-bottom or
//    bottom-to-top text).
//
// Deviations from standard:
//  * Section 4.5 of the spec indicates that all flex items have a default
//    minimum main size. For text blocks, for example, this is the width of the
//    widest word. Calculating the minimum width is expensive, so we forego it
//    and assume a default minimum main size of 0.
//  * Min/Max sizes in the main axis are not honored when resolving flexible
//    lengths.
//  * The spec indicates that the default value for 'flexDirection' is 'row',
//    but the algorithm below assumes a default of 'column'.
//
// Input parameters:
//    - node: current node to be sized and layed out
//    - availableWidth & availableHeight: available size to be used for sizing
//      the node or ABI33_0_0YGUndefined if the size is not available; interpretation
//      depends on layout flags
//    - ownerDirection: the inline (text) direction within the owner
//      (left-to-right or right-to-left)
//    - widthMeasureMode: indicates the sizing rules for the width (see below
//      for explanation)
//    - heightMeasureMode: indicates the sizing rules for the height (see below
//      for explanation)
//    - performLayout: specifies whether the caller is interested in just the
//      dimensions of the node or it requires the entire node and its subtree to
//      be layed out (with final positions)
//
// Details:
//    This routine is called recursively to lay out subtrees of flexbox
//    elements. It uses the information in node.style, which is treated as a
//    read-only input. It is responsible for setting the layout.direction and
//    layout.measuredDimensions fields for the input node as well as the
//    layout.position and layout.lineIndex fields for its child nodes. The
//    layout.measuredDimensions field includes any border or padding for the
//    node but does not include margins.
//
//    The spec describes four different layout modes: "fill available", "max
//    content", "min content", and "fit content". Of these, we don't use "min
//    content" because we don't support default minimum main sizes (see above
//    for details). Each of our measure modes maps to a layout mode from the
//    spec (https://www.w3.org/TR/CSS3-sizing/#terms):
//      - ABI33_0_0YGMeasureModeUndefined: max content
//      - ABI33_0_0YGMeasureModeExactly: fill available
//      - ABI33_0_0YGMeasureModeAtMost: fit content
//
//    When calling ABI33_0_0YGNodelayoutImpl and ABI33_0_0YGLayoutNodeInternal, if the caller
//    passes an available size of undefined then it must also pass a measure
//    mode of ABI33_0_0YGMeasureModeUndefined in that dimension.
//
static void ABI33_0_0YGNodelayoutImpl(
    const ABI33_0_0YGNodeRef node,
    const float availableWidth,
    const float availableHeight,
    const ABI33_0_0YGDirection ownerDirection,
    const ABI33_0_0YGMeasureMode widthMeasureMode,
    const ABI33_0_0YGMeasureMode heightMeasureMode,
    const float ownerWidth,
    const float ownerHeight,
    const bool performLayout,
    const ABI33_0_0YGConfigRef config,
    ABI33_0_0YGMarkerLayoutData& layoutMarkerData) {
  ABI33_0_0YGAssertWithNode(
      node,
      ABI33_0_0YGFloatIsUndefined(availableWidth)
          ? widthMeasureMode == ABI33_0_0YGMeasureModeUndefined
          : true,
      "availableWidth is indefinite so widthMeasureMode must be "
      "ABI33_0_0YGMeasureModeUndefined");
  ABI33_0_0YGAssertWithNode(
      node,
      ABI33_0_0YGFloatIsUndefined(availableHeight)
          ? heightMeasureMode == ABI33_0_0YGMeasureModeUndefined
          : true,
      "availableHeight is indefinite so heightMeasureMode must be "
      "ABI33_0_0YGMeasureModeUndefined");

  (performLayout ? layoutMarkerData.layouts : layoutMarkerData.measures) += 1;

  // Set the resolved resolution in the node's layout.
  const ABI33_0_0YGDirection direction = node->resolveDirection(ownerDirection);
  node->setLayoutDirection(direction);

  const ABI33_0_0YGFlexDirection flexRowDirection =
      ABI33_0_0YGResolveFlexDirection(ABI33_0_0YGFlexDirectionRow, direction);
  const ABI33_0_0YGFlexDirection flexColumnDirection =
      ABI33_0_0YGResolveFlexDirection(ABI33_0_0YGFlexDirectionColumn, direction);

  node->setLayoutMargin(
      node->getLeadingMargin(flexRowDirection, ownerWidth).unwrap(),
      ABI33_0_0YGEdgeStart);
  node->setLayoutMargin(
      node->getTrailingMargin(flexRowDirection, ownerWidth).unwrap(),
      ABI33_0_0YGEdgeEnd);
  node->setLayoutMargin(
      node->getLeadingMargin(flexColumnDirection, ownerWidth).unwrap(),
      ABI33_0_0YGEdgeTop);
  node->setLayoutMargin(
      node->getTrailingMargin(flexColumnDirection, ownerWidth).unwrap(),
      ABI33_0_0YGEdgeBottom);

  node->setLayoutBorder(node->getLeadingBorder(flexRowDirection), ABI33_0_0YGEdgeStart);
  node->setLayoutBorder(node->getTrailingBorder(flexRowDirection), ABI33_0_0YGEdgeEnd);
  node->setLayoutBorder(node->getLeadingBorder(flexColumnDirection), ABI33_0_0YGEdgeTop);
  node->setLayoutBorder(
      node->getTrailingBorder(flexColumnDirection), ABI33_0_0YGEdgeBottom);

  node->setLayoutPadding(
      node->getLeadingPadding(flexRowDirection, ownerWidth).unwrap(),
      ABI33_0_0YGEdgeStart);
  node->setLayoutPadding(
      node->getTrailingPadding(flexRowDirection, ownerWidth).unwrap(),
      ABI33_0_0YGEdgeEnd);
  node->setLayoutPadding(
      node->getLeadingPadding(flexColumnDirection, ownerWidth).unwrap(),
      ABI33_0_0YGEdgeTop);
  node->setLayoutPadding(
      node->getTrailingPadding(flexColumnDirection, ownerWidth).unwrap(),
      ABI33_0_0YGEdgeBottom);

  if (node->getMeasure() != nullptr) {
    ABI33_0_0YGNodeWithMeasureFuncSetMeasuredDimensions(
        node,
        availableWidth,
        availableHeight,
        widthMeasureMode,
        heightMeasureMode,
        ownerWidth,
        ownerHeight);
    return;
  }

  const uint32_t childCount = ABI33_0_0YGNodeGetChildCount(node);
  if (childCount == 0) {
    ABI33_0_0YGNodeEmptyContainerSetMeasuredDimensions(
        node,
        availableWidth,
        availableHeight,
        widthMeasureMode,
        heightMeasureMode,
        ownerWidth,
        ownerHeight);
    return;
  }

  // If we're not being asked to perform a full layout we can skip the algorithm
  // if we already know the size
  if (!performLayout &&
      ABI33_0_0YGNodeFixedSizeSetMeasuredDimensions(
          node,
          availableWidth,
          availableHeight,
          widthMeasureMode,
          heightMeasureMode,
          ownerWidth,
          ownerHeight)) {
    return;
  }

  // At this point we know we're going to perform work. Ensure that each child
  // has a mutable copy.
  node->cloneChildrenIfNeeded();
  // Reset layout flags, as they could have changed.
  node->setLayoutHadOverflow(false);

  // STEP 1: CALCULATE VALUES FOR REMAINDER OF ALGORITHM
  const ABI33_0_0YGFlexDirection mainAxis =
      ABI33_0_0YGResolveFlexDirection(node->getStyle().flexDirection, direction);
  const ABI33_0_0YGFlexDirection crossAxis = ABI33_0_0YGFlexDirectionCross(mainAxis, direction);
  const bool isMainAxisRow = ABI33_0_0YGFlexDirectionIsRow(mainAxis);
  const bool isNodeFlexWrap = node->getStyle().flexWrap != ABI33_0_0YGWrapNoWrap;

  const float mainAxisownerSize = isMainAxisRow ? ownerWidth : ownerHeight;
  const float crossAxisownerSize = isMainAxisRow ? ownerHeight : ownerWidth;

  const float leadingPaddingAndBorderCross =
      node->getLeadingPaddingAndBorder(crossAxis, ownerWidth).unwrap();
  const float paddingAndBorderAxisMain =
      ABI33_0_0YGNodePaddingAndBorderForAxis(node, mainAxis, ownerWidth);
  const float paddingAndBorderAxisCross =
      ABI33_0_0YGNodePaddingAndBorderForAxis(node, crossAxis, ownerWidth);

  ABI33_0_0YGMeasureMode measureModeMainDim =
      isMainAxisRow ? widthMeasureMode : heightMeasureMode;
  ABI33_0_0YGMeasureMode measureModeCrossDim =
      isMainAxisRow ? heightMeasureMode : widthMeasureMode;

  const float paddingAndBorderAxisRow =
      isMainAxisRow ? paddingAndBorderAxisMain : paddingAndBorderAxisCross;
  const float paddingAndBorderAxisColumn =
      isMainAxisRow ? paddingAndBorderAxisCross : paddingAndBorderAxisMain;

  const float marginAxisRow =
      node->getMarginForAxis(ABI33_0_0YGFlexDirectionRow, ownerWidth).unwrap();
  const float marginAxisColumn =
      node->getMarginForAxis(ABI33_0_0YGFlexDirectionColumn, ownerWidth).unwrap();

  const float minInnerWidth =
      ABI33_0_0YGResolveValue(
          node->getStyle().minDimensions[ABI33_0_0YGDimensionWidth], ownerWidth)
          .unwrap() -
      paddingAndBorderAxisRow;
  const float maxInnerWidth =
      ABI33_0_0YGResolveValue(
          node->getStyle().maxDimensions[ABI33_0_0YGDimensionWidth], ownerWidth)
          .unwrap() -
      paddingAndBorderAxisRow;
  const float minInnerHeight =
      ABI33_0_0YGResolveValue(
          node->getStyle().minDimensions[ABI33_0_0YGDimensionHeight], ownerHeight)
          .unwrap() -
      paddingAndBorderAxisColumn;
  const float maxInnerHeight =
      ABI33_0_0YGResolveValue(
          node->getStyle().maxDimensions[ABI33_0_0YGDimensionHeight], ownerHeight)
          .unwrap() -
      paddingAndBorderAxisColumn;

  const float minInnerMainDim = isMainAxisRow ? minInnerWidth : minInnerHeight;
  const float maxInnerMainDim = isMainAxisRow ? maxInnerWidth : maxInnerHeight;

  // STEP 2: DETERMINE AVAILABLE SIZE IN MAIN AND CROSS DIRECTIONS

  float availableInnerWidth = ABI33_0_0YGNodeCalculateAvailableInnerDim(
      node, ABI33_0_0YGFlexDirectionRow, availableWidth, ownerWidth);
  float availableInnerHeight = ABI33_0_0YGNodeCalculateAvailableInnerDim(
      node, ABI33_0_0YGFlexDirectionColumn, availableHeight, ownerHeight);

  float availableInnerMainDim =
      isMainAxisRow ? availableInnerWidth : availableInnerHeight;
  const float availableInnerCrossDim =
      isMainAxisRow ? availableInnerHeight : availableInnerWidth;

  // STEP 3: DETERMINE FLEX BASIS FOR EACH ITEM

  float totalOuterFlexBasis = ABI33_0_0YGNodeComputeFlexBasisForChildren(
      node,
      availableInnerWidth,
      availableInnerHeight,
      widthMeasureMode,
      heightMeasureMode,
      direction,
      mainAxis,
      config,
      performLayout,
      layoutMarkerData);

  const bool flexBasisOverflows = measureModeMainDim == ABI33_0_0YGMeasureModeUndefined
      ? false
      : totalOuterFlexBasis > availableInnerMainDim;
  if (isNodeFlexWrap && flexBasisOverflows &&
      measureModeMainDim == ABI33_0_0YGMeasureModeAtMost) {
    measureModeMainDim = ABI33_0_0YGMeasureModeExactly;
  }
  // STEP 4: COLLECT FLEX ITEMS INTO FLEX LINES

  // Indexes of children that represent the first and last items in the line.
  uint32_t startOfLineIndex = 0;
  uint32_t endOfLineIndex = 0;

  // Number of lines.
  uint32_t lineCount = 0;

  // Accumulated cross dimensions of all lines so far.
  float totalLineCrossDim = 0;

  // Max main dimension of all the lines.
  float maxLineMainDim = 0;
  ABI33_0_0YGCollectFlexItemsRowValues collectedFlexItemsValues;
  for (; endOfLineIndex < childCount;
       lineCount++, startOfLineIndex = endOfLineIndex) {
    collectedFlexItemsValues = ABI33_0_0YGCalculateCollectFlexItemsRowValues(
        node,
        ownerDirection,
        mainAxisownerSize,
        availableInnerWidth,
        availableInnerMainDim,
        startOfLineIndex,
        lineCount);
    endOfLineIndex = collectedFlexItemsValues.endOfLineIndex;

    // If we don't need to measure the cross axis, we can skip the entire flex
    // step.
    const bool canSkipFlex =
        !performLayout && measureModeCrossDim == ABI33_0_0YGMeasureModeExactly;

    // STEP 5: RESOLVING FLEXIBLE LENGTHS ON MAIN AXIS
    // Calculate the remaining available space that needs to be allocated. If
    // the main dimension size isn't known, it is computed based on the line
    // length, so there's no more space left to distribute.

    bool sizeBasedOnContent = false;
    // If we don't measure with exact main dimension we want to ensure we don't
    // violate min and max
    if (measureModeMainDim != ABI33_0_0YGMeasureModeExactly) {
      if (!ABI33_0_0YGFloatIsUndefined(minInnerMainDim) &&
          collectedFlexItemsValues.sizeConsumedOnCurrentLine <
              minInnerMainDim) {
        availableInnerMainDim = minInnerMainDim;
      } else if (
          !ABI33_0_0YGFloatIsUndefined(maxInnerMainDim) &&
          collectedFlexItemsValues.sizeConsumedOnCurrentLine >
              maxInnerMainDim) {
        availableInnerMainDim = maxInnerMainDim;
      } else {
        if (!node->getConfig()->useLegacyStretchBehaviour &&
            ((ABI33_0_0YGFloatIsUndefined(
                  collectedFlexItemsValues.totalFlexGrowFactors) &&
              collectedFlexItemsValues.totalFlexGrowFactors == 0) ||
             (ABI33_0_0YGFloatIsUndefined(node->resolveFlexGrow()) &&
              node->resolveFlexGrow() == 0))) {
          // If we don't have any children to flex or we can't flex the node
          // itself, space we've used is all space we need. Root node also
          // should be shrunk to minimum
          availableInnerMainDim =
              collectedFlexItemsValues.sizeConsumedOnCurrentLine;
        }

        if (node->getConfig()->useLegacyStretchBehaviour) {
          node->setLayoutDidUseLegacyFlag(true);
        }
        sizeBasedOnContent = !node->getConfig()->useLegacyStretchBehaviour;
      }
    }

    if (!sizeBasedOnContent && !ABI33_0_0YGFloatIsUndefined(availableInnerMainDim)) {
      collectedFlexItemsValues.remainingFreeSpace = availableInnerMainDim -
          collectedFlexItemsValues.sizeConsumedOnCurrentLine;
    } else if (collectedFlexItemsValues.sizeConsumedOnCurrentLine < 0) {
      // availableInnerMainDim is indefinite which means the node is being sized
      // based on its content. sizeConsumedOnCurrentLine is negative which means
      // the node will allocate 0 points for its content. Consequently,
      // remainingFreeSpace is 0 - sizeConsumedOnCurrentLine.
      collectedFlexItemsValues.remainingFreeSpace =
          -collectedFlexItemsValues.sizeConsumedOnCurrentLine;
    }

    if (!canSkipFlex) {
      ABI33_0_0YGResolveFlexibleLength(
          node,
          collectedFlexItemsValues,
          mainAxis,
          crossAxis,
          mainAxisownerSize,
          availableInnerMainDim,
          availableInnerCrossDim,
          availableInnerWidth,
          availableInnerHeight,
          flexBasisOverflows,
          measureModeCrossDim,
          performLayout,
          config,
          layoutMarkerData);
    }

    node->setLayoutHadOverflow(
        node->getLayout().hadOverflow |
        (collectedFlexItemsValues.remainingFreeSpace < 0));

    // STEP 6: MAIN-AXIS JUSTIFICATION & CROSS-AXIS SIZE DETERMINATION

    // At this point, all the children have their dimensions set in the main
    // axis. Their dimensions are also set in the cross axis with the exception
    // of items that are aligned "stretch". We need to compute these stretch
    // values and set the final positions.

    ABI33_0_0YGJustifyMainAxis(
        node,
        collectedFlexItemsValues,
        startOfLineIndex,
        mainAxis,
        crossAxis,
        measureModeMainDim,
        measureModeCrossDim,
        mainAxisownerSize,
        ownerWidth,
        availableInnerMainDim,
        availableInnerCrossDim,
        availableInnerWidth,
        performLayout);

    float containerCrossAxis = availableInnerCrossDim;
    if (measureModeCrossDim == ABI33_0_0YGMeasureModeUndefined ||
        measureModeCrossDim == ABI33_0_0YGMeasureModeAtMost) {
      // Compute the cross axis from the max cross dimension of the children.
      containerCrossAxis =
          ABI33_0_0YGNodeBoundAxis(
              node,
              crossAxis,
              collectedFlexItemsValues.crossDim + paddingAndBorderAxisCross,
              crossAxisownerSize,
              ownerWidth) -
          paddingAndBorderAxisCross;
    }

    // If there's no flex wrap, the cross dimension is defined by the container.
    if (!isNodeFlexWrap && measureModeCrossDim == ABI33_0_0YGMeasureModeExactly) {
      collectedFlexItemsValues.crossDim = availableInnerCrossDim;
    }

    // Clamp to the min/max size specified on the container.
    collectedFlexItemsValues.crossDim =
        ABI33_0_0YGNodeBoundAxis(
            node,
            crossAxis,
            collectedFlexItemsValues.crossDim + paddingAndBorderAxisCross,
            crossAxisownerSize,
            ownerWidth) -
        paddingAndBorderAxisCross;

    // STEP 7: CROSS-AXIS ALIGNMENT
    // We can skip child alignment if we're just measuring the container.
    if (performLayout) {
      for (uint32_t i = startOfLineIndex; i < endOfLineIndex; i++) {
        const ABI33_0_0YGNodeRef child = node->getChild(i);
        if (child->getStyle().display == ABI33_0_0YGDisplayNone) {
          continue;
        }
        if (child->getStyle().positionType == ABI33_0_0YGPositionTypeAbsolute) {
          // If the child is absolutely positioned and has a
          // top/left/bottom/right set, override all the previously computed
          // positions to set it correctly.
          const bool isChildLeadingPosDefined =
              child->isLeadingPositionDefined(crossAxis);
          if (isChildLeadingPosDefined) {
            child->setLayoutPosition(
                child->getLeadingPosition(crossAxis, availableInnerCrossDim)
                        .unwrap() +
                    node->getLeadingBorder(crossAxis) +
                    child->getLeadingMargin(crossAxis, availableInnerWidth)
                        .unwrap(),
                pos[crossAxis]);
          }
          // If leading position is not defined or calculations result in Nan,
          // default to border + margin
          if (!isChildLeadingPosDefined ||
              ABI33_0_0YGFloatIsUndefined(child->getLayout().position[pos[crossAxis]])) {
            child->setLayoutPosition(
                node->getLeadingBorder(crossAxis) +
                    child->getLeadingMargin(crossAxis, availableInnerWidth)
                        .unwrap(),
                pos[crossAxis]);
          }
        } else {
          float leadingCrossDim = leadingPaddingAndBorderCross;

          // For a relative children, we're either using alignItems (owner) or
          // alignSelf (child) in order to determine the position in the cross
          // axis
          const ABI33_0_0YGAlign alignItem = ABI33_0_0YGNodeAlignItem(node, child);

          // If the child uses align stretch, we need to lay it out one more
          // time, this time forcing the cross-axis size to be the computed
          // cross size for the current line.
          if (alignItem == ABI33_0_0YGAlignStretch &&
              child->marginLeadingValue(crossAxis).unit != ABI33_0_0YGUnitAuto &&
              child->marginTrailingValue(crossAxis).unit != ABI33_0_0YGUnitAuto) {
            // If the child defines a definite size for its cross axis, there's
            // no need to stretch.
            if (!ABI33_0_0YGNodeIsStyleDimDefined(
                    child, crossAxis, availableInnerCrossDim)) {
              float childMainSize =
                  child->getLayout().measuredDimensions[dim[mainAxis]];
              float childCrossSize =
                  !child->getStyle().aspectRatio.isUndefined()
                  ? child->getMarginForAxis(crossAxis, availableInnerWidth)
                          .unwrap() +
                      (isMainAxisRow ? childMainSize /
                               child->getStyle().aspectRatio.unwrap()
                                     : childMainSize *
                               child->getStyle().aspectRatio.unwrap())
                  : collectedFlexItemsValues.crossDim;

              childMainSize +=
                  child->getMarginForAxis(mainAxis, availableInnerWidth)
                      .unwrap();

              ABI33_0_0YGMeasureMode childMainMeasureMode = ABI33_0_0YGMeasureModeExactly;
              ABI33_0_0YGMeasureMode childCrossMeasureMode = ABI33_0_0YGMeasureModeExactly;
              ABI33_0_0YGConstrainMaxSizeForMode(
                  child,
                  mainAxis,
                  availableInnerMainDim,
                  availableInnerWidth,
                  &childMainMeasureMode,
                  &childMainSize);
              ABI33_0_0YGConstrainMaxSizeForMode(
                  child,
                  crossAxis,
                  availableInnerCrossDim,
                  availableInnerWidth,
                  &childCrossMeasureMode,
                  &childCrossSize);

              const float childWidth =
                  isMainAxisRow ? childMainSize : childCrossSize;
              const float childHeight =
                  !isMainAxisRow ? childMainSize : childCrossSize;

              const ABI33_0_0YGMeasureMode childWidthMeasureMode =
                  ABI33_0_0YGFloatIsUndefined(childWidth) ? ABI33_0_0YGMeasureModeUndefined
                                                 : ABI33_0_0YGMeasureModeExactly;
              const ABI33_0_0YGMeasureMode childHeightMeasureMode =
                  ABI33_0_0YGFloatIsUndefined(childHeight) ? ABI33_0_0YGMeasureModeUndefined
                                                  : ABI33_0_0YGMeasureModeExactly;

              ABI33_0_0YGLayoutNodeInternal(
                  child,
                  childWidth,
                  childHeight,
                  direction,
                  childWidthMeasureMode,
                  childHeightMeasureMode,
                  availableInnerWidth,
                  availableInnerHeight,
                  true,
                  "stretch",
                  config,
                  layoutMarkerData);
            }
          } else {
            const float remainingCrossDim = containerCrossAxis -
                ABI33_0_0YGNodeDimWithMargin(child, crossAxis, availableInnerWidth);

            if (child->marginLeadingValue(crossAxis).unit == ABI33_0_0YGUnitAuto &&
                child->marginTrailingValue(crossAxis).unit == ABI33_0_0YGUnitAuto) {
              leadingCrossDim += ABI33_0_0YGFloatMax(0.0f, remainingCrossDim / 2);
            } else if (
                child->marginTrailingValue(crossAxis).unit == ABI33_0_0YGUnitAuto) {
              // No-Op
            } else if (
                child->marginLeadingValue(crossAxis).unit == ABI33_0_0YGUnitAuto) {
              leadingCrossDim += ABI33_0_0YGFloatMax(0.0f, remainingCrossDim);
            } else if (alignItem == ABI33_0_0YGAlignFlexStart) {
              // No-Op
            } else if (alignItem == ABI33_0_0YGAlignCenter) {
              leadingCrossDim += remainingCrossDim / 2;
            } else {
              leadingCrossDim += remainingCrossDim;
            }
          }
          // And we apply the position
          child->setLayoutPosition(
              child->getLayout().position[pos[crossAxis]] + totalLineCrossDim +
                  leadingCrossDim,
              pos[crossAxis]);
        }
      }
    }

    totalLineCrossDim += collectedFlexItemsValues.crossDim;
    maxLineMainDim =
        ABI33_0_0YGFloatMax(maxLineMainDim, collectedFlexItemsValues.mainDim);
  }

  // STEP 8: MULTI-LINE CONTENT ALIGNMENT
  // currentLead stores the size of the cross dim
  if (performLayout && (lineCount > 1 || ABI33_0_0YGIsBaselineLayout(node))) {
    float crossDimLead = 0;
    float currentLead = leadingPaddingAndBorderCross;
    if (!ABI33_0_0YGFloatIsUndefined(availableInnerCrossDim)) {
      const float remainingAlignContentDim =
          availableInnerCrossDim - totalLineCrossDim;
      switch (node->getStyle().alignContent) {
        case ABI33_0_0YGAlignFlexEnd:
          currentLead += remainingAlignContentDim;
          break;
        case ABI33_0_0YGAlignCenter:
          currentLead += remainingAlignContentDim / 2;
          break;
        case ABI33_0_0YGAlignStretch:
          if (availableInnerCrossDim > totalLineCrossDim) {
            crossDimLead = remainingAlignContentDim / lineCount;
          }
          break;
        case ABI33_0_0YGAlignSpaceAround:
          if (availableInnerCrossDim > totalLineCrossDim) {
            currentLead += remainingAlignContentDim / (2 * lineCount);
            if (lineCount > 1) {
              crossDimLead = remainingAlignContentDim / lineCount;
            }
          } else {
            currentLead += remainingAlignContentDim / 2;
          }
          break;
        case ABI33_0_0YGAlignSpaceBetween:
          if (availableInnerCrossDim > totalLineCrossDim && lineCount > 1) {
            crossDimLead = remainingAlignContentDim / (lineCount - 1);
          }
          break;
        case ABI33_0_0YGAlignAuto:
        case ABI33_0_0YGAlignFlexStart:
        case ABI33_0_0YGAlignBaseline:
          break;
      }
    }
    uint32_t endIndex = 0;
    for (uint32_t i = 0; i < lineCount; i++) {
      const uint32_t startIndex = endIndex;
      uint32_t ii;

      // compute the line's height and find the endIndex
      float lineHeight = 0;
      float maxAscentForCurrentLine = 0;
      float maxDescentForCurrentLine = 0;
      for (ii = startIndex; ii < childCount; ii++) {
        const ABI33_0_0YGNodeRef child = node->getChild(ii);
        if (child->getStyle().display == ABI33_0_0YGDisplayNone) {
          continue;
        }
        if (child->getStyle().positionType == ABI33_0_0YGPositionTypeRelative) {
          if (child->getLineIndex() != i) {
            break;
          }
          if (ABI33_0_0YGNodeIsLayoutDimDefined(child, crossAxis)) {
            lineHeight = ABI33_0_0YGFloatMax(
                lineHeight,
                child->getLayout().measuredDimensions[dim[crossAxis]] +
                    child->getMarginForAxis(crossAxis, availableInnerWidth)
                        .unwrap());
          }
          if (ABI33_0_0YGNodeAlignItem(node, child) == ABI33_0_0YGAlignBaseline) {
            const float ascent = ABI33_0_0YGBaseline(child) +
                child
                    ->getLeadingMargin(
                        ABI33_0_0YGFlexDirectionColumn, availableInnerWidth)
                    .unwrap();
            const float descent =
                child->getLayout().measuredDimensions[ABI33_0_0YGDimensionHeight] +
                child
                    ->getMarginForAxis(
                        ABI33_0_0YGFlexDirectionColumn, availableInnerWidth)
                    .unwrap() -
                ascent;
            maxAscentForCurrentLine =
                ABI33_0_0YGFloatMax(maxAscentForCurrentLine, ascent);
            maxDescentForCurrentLine =
                ABI33_0_0YGFloatMax(maxDescentForCurrentLine, descent);
            lineHeight = ABI33_0_0YGFloatMax(
                lineHeight, maxAscentForCurrentLine + maxDescentForCurrentLine);
          }
        }
      }
      endIndex = ii;
      lineHeight += crossDimLead;

      if (performLayout) {
        for (ii = startIndex; ii < endIndex; ii++) {
          const ABI33_0_0YGNodeRef child = node->getChild(ii);
          if (child->getStyle().display == ABI33_0_0YGDisplayNone) {
            continue;
          }
          if (child->getStyle().positionType == ABI33_0_0YGPositionTypeRelative) {
            switch (ABI33_0_0YGNodeAlignItem(node, child)) {
              case ABI33_0_0YGAlignFlexStart: {
                child->setLayoutPosition(
                    currentLead +
                        child->getLeadingMargin(crossAxis, availableInnerWidth)
                            .unwrap(),
                    pos[crossAxis]);
                break;
              }
              case ABI33_0_0YGAlignFlexEnd: {
                child->setLayoutPosition(
                    currentLead + lineHeight -
                        child->getTrailingMargin(crossAxis, availableInnerWidth)
                            .unwrap() -
                        child->getLayout().measuredDimensions[dim[crossAxis]],
                    pos[crossAxis]);
                break;
              }
              case ABI33_0_0YGAlignCenter: {
                float childHeight =
                    child->getLayout().measuredDimensions[dim[crossAxis]];

                child->setLayoutPosition(
                    currentLead + (lineHeight - childHeight) / 2,
                    pos[crossAxis]);
                break;
              }
              case ABI33_0_0YGAlignStretch: {
                child->setLayoutPosition(
                    currentLead +
                        child->getLeadingMargin(crossAxis, availableInnerWidth)
                            .unwrap(),
                    pos[crossAxis]);

                // Remeasure child with the line height as it as been only
                // measured with the owners height yet.
                if (!ABI33_0_0YGNodeIsStyleDimDefined(
                        child, crossAxis, availableInnerCrossDim)) {
                  const float childWidth = isMainAxisRow
                      ? (child->getLayout()
                             .measuredDimensions[ABI33_0_0YGDimensionWidth] +
                         child->getMarginForAxis(mainAxis, availableInnerWidth)
                             .unwrap())
                      : lineHeight;

                  const float childHeight = !isMainAxisRow
                      ? (child->getLayout()
                             .measuredDimensions[ABI33_0_0YGDimensionHeight] +
                         child->getMarginForAxis(crossAxis, availableInnerWidth)
                             .unwrap())
                      : lineHeight;

                  if (!(ABI33_0_0YGFloatsEqual(
                            childWidth,
                            child->getLayout()
                                .measuredDimensions[ABI33_0_0YGDimensionWidth]) &&
                        ABI33_0_0YGFloatsEqual(
                            childHeight,
                            child->getLayout()
                                .measuredDimensions[ABI33_0_0YGDimensionHeight]))) {
                    ABI33_0_0YGLayoutNodeInternal(
                        child,
                        childWidth,
                        childHeight,
                        direction,
                        ABI33_0_0YGMeasureModeExactly,
                        ABI33_0_0YGMeasureModeExactly,
                        availableInnerWidth,
                        availableInnerHeight,
                        true,
                        "multiline-stretch",
                        config,
                        layoutMarkerData);
                  }
                }
                break;
              }
              case ABI33_0_0YGAlignBaseline: {
                child->setLayoutPosition(
                    currentLead + maxAscentForCurrentLine - ABI33_0_0YGBaseline(child) +
                        child
                            ->getLeadingPosition(
                                ABI33_0_0YGFlexDirectionColumn, availableInnerCrossDim)
                            .unwrap(),
                    ABI33_0_0YGEdgeTop);

                break;
              }
              case ABI33_0_0YGAlignAuto:
              case ABI33_0_0YGAlignSpaceBetween:
              case ABI33_0_0YGAlignSpaceAround:
                break;
            }
          }
        }
      }
      currentLead += lineHeight;
    }
  }

  // STEP 9: COMPUTING FINAL DIMENSIONS

  node->setLayoutMeasuredDimension(
      ABI33_0_0YGNodeBoundAxis(
          node,
          ABI33_0_0YGFlexDirectionRow,
          availableWidth - marginAxisRow,
          ownerWidth,
          ownerWidth),
      ABI33_0_0YGDimensionWidth);

  node->setLayoutMeasuredDimension(
      ABI33_0_0YGNodeBoundAxis(
          node,
          ABI33_0_0YGFlexDirectionColumn,
          availableHeight - marginAxisColumn,
          ownerHeight,
          ownerWidth),
      ABI33_0_0YGDimensionHeight);

  // If the user didn't specify a width or height for the node, set the
  // dimensions based on the children.
  if (measureModeMainDim == ABI33_0_0YGMeasureModeUndefined ||
      (node->getStyle().overflow != ABI33_0_0YGOverflowScroll &&
       measureModeMainDim == ABI33_0_0YGMeasureModeAtMost)) {
    // Clamp the size to the min/max size, if specified, and make sure it
    // doesn't go below the padding and border amount.
    node->setLayoutMeasuredDimension(
        ABI33_0_0YGNodeBoundAxis(
            node, mainAxis, maxLineMainDim, mainAxisownerSize, ownerWidth),
        dim[mainAxis]);

  } else if (
      measureModeMainDim == ABI33_0_0YGMeasureModeAtMost &&
      node->getStyle().overflow == ABI33_0_0YGOverflowScroll) {
    node->setLayoutMeasuredDimension(
        ABI33_0_0YGFloatMax(
            ABI33_0_0YGFloatMin(
                availableInnerMainDim + paddingAndBorderAxisMain,
                ABI33_0_0YGNodeBoundAxisWithinMinAndMax(
                    node,
                    mainAxis,
                    ABI33_0_0YGFloatOptional{maxLineMainDim},
                    mainAxisownerSize)
                    .unwrap()),
            paddingAndBorderAxisMain),
        dim[mainAxis]);
  }

  if (measureModeCrossDim == ABI33_0_0YGMeasureModeUndefined ||
      (node->getStyle().overflow != ABI33_0_0YGOverflowScroll &&
       measureModeCrossDim == ABI33_0_0YGMeasureModeAtMost)) {
    // Clamp the size to the min/max size, if specified, and make sure it
    // doesn't go below the padding and border amount.
    node->setLayoutMeasuredDimension(
        ABI33_0_0YGNodeBoundAxis(
            node,
            crossAxis,
            totalLineCrossDim + paddingAndBorderAxisCross,
            crossAxisownerSize,
            ownerWidth),
        dim[crossAxis]);

  } else if (
      measureModeCrossDim == ABI33_0_0YGMeasureModeAtMost &&
      node->getStyle().overflow == ABI33_0_0YGOverflowScroll) {
    node->setLayoutMeasuredDimension(
        ABI33_0_0YGFloatMax(
            ABI33_0_0YGFloatMin(
                availableInnerCrossDim + paddingAndBorderAxisCross,
                ABI33_0_0YGNodeBoundAxisWithinMinAndMax(
                    node,
                    crossAxis,
                    ABI33_0_0YGFloatOptional{totalLineCrossDim +
                                    paddingAndBorderAxisCross},
                    crossAxisownerSize)
                    .unwrap()),
            paddingAndBorderAxisCross),
        dim[crossAxis]);
  }

  // As we only wrapped in normal direction yet, we need to reverse the
  // positions on wrap-reverse.
  if (performLayout && node->getStyle().flexWrap == ABI33_0_0YGWrapWrapReverse) {
    for (uint32_t i = 0; i < childCount; i++) {
      const ABI33_0_0YGNodeRef child = ABI33_0_0YGNodeGetChild(node, i);
      if (child->getStyle().positionType == ABI33_0_0YGPositionTypeRelative) {
        child->setLayoutPosition(
            node->getLayout().measuredDimensions[dim[crossAxis]] -
                child->getLayout().position[pos[crossAxis]] -
                child->getLayout().measuredDimensions[dim[crossAxis]],
            pos[crossAxis]);
      }
    }
  }

  if (performLayout) {
    // STEP 10: SIZING AND POSITIONING ABSOLUTE CHILDREN
    for (auto child : node->getChildren()) {
      if (child->getStyle().positionType != ABI33_0_0YGPositionTypeAbsolute) {
        continue;
      }
      ABI33_0_0YGNodeAbsoluteLayoutChild(
          node,
          child,
          availableInnerWidth,
          isMainAxisRow ? measureModeMainDim : measureModeCrossDim,
          availableInnerHeight,
          direction,
          config,
          layoutMarkerData);
    }

    // STEP 11: SETTING TRAILING POSITIONS FOR CHILDREN
    const bool needsMainTrailingPos = mainAxis == ABI33_0_0YGFlexDirectionRowReverse ||
        mainAxis == ABI33_0_0YGFlexDirectionColumnReverse;
    const bool needsCrossTrailingPos = crossAxis == ABI33_0_0YGFlexDirectionRowReverse ||
        crossAxis == ABI33_0_0YGFlexDirectionColumnReverse;

    // Set trailing position if necessary.
    if (needsMainTrailingPos || needsCrossTrailingPos) {
      for (uint32_t i = 0; i < childCount; i++) {
        const ABI33_0_0YGNodeRef child = node->getChild(i);
        if (child->getStyle().display == ABI33_0_0YGDisplayNone) {
          continue;
        }
        if (needsMainTrailingPos) {
          ABI33_0_0YGNodeSetChildTrailingPosition(node, child, mainAxis);
        }

        if (needsCrossTrailingPos) {
          ABI33_0_0YGNodeSetChildTrailingPosition(node, child, crossAxis);
        }
      }
    }
  }
}

uint32_t gDepth = 0;
bool gPrintChanges = false;
bool gPrintSkips = false;

static const char* spacer =
    "                                                            ";

static const char* ABI33_0_0YGSpacer(const unsigned long level) {
  const size_t spacerLen = strlen(spacer);
  if (level > spacerLen) {
    return &spacer[0];
  } else {
    return &spacer[spacerLen - level];
  }
}

static const char* ABI33_0_0YGMeasureModeName(
    const ABI33_0_0YGMeasureMode mode,
    const bool performLayout) {
  constexpr auto N = enums::count<ABI33_0_0YGMeasureMode>();
  const char* kMeasureModeNames[N] = {"UNDEFINED", "ABI33_0_0EXACTLY", "AT_MOST"};
  const char* kLayoutModeNames[N] = {
      "LAY_UNDEFINED", "LAY_EXACTLY", "LAY_AT_MOST"};

  if (mode >= N) {
    return "";
  }

  return performLayout ? kLayoutModeNames[mode] : kMeasureModeNames[mode];
}

static inline bool ABI33_0_0YGMeasureModeSizeIsExactAndMatchesOldMeasuredSize(
    ABI33_0_0YGMeasureMode sizeMode,
    float size,
    float lastComputedSize) {
  return sizeMode == ABI33_0_0YGMeasureModeExactly &&
      ABI33_0_0YGFloatsEqual(size, lastComputedSize);
}

static inline bool ABI33_0_0YGMeasureModeOldSizeIsUnspecifiedAndStillFits(
    ABI33_0_0YGMeasureMode sizeMode,
    float size,
    ABI33_0_0YGMeasureMode lastSizeMode,
    float lastComputedSize) {
  return sizeMode == ABI33_0_0YGMeasureModeAtMost &&
      lastSizeMode == ABI33_0_0YGMeasureModeUndefined &&
      (size >= lastComputedSize || ABI33_0_0YGFloatsEqual(size, lastComputedSize));
}

static inline bool ABI33_0_0YGMeasureModeNewMeasureSizeIsStricterAndStillValid(
    ABI33_0_0YGMeasureMode sizeMode,
    float size,
    ABI33_0_0YGMeasureMode lastSizeMode,
    float lastSize,
    float lastComputedSize) {
  return lastSizeMode == ABI33_0_0YGMeasureModeAtMost &&
      sizeMode == ABI33_0_0YGMeasureModeAtMost && !ABI33_0_0YGFloatIsUndefined(lastSize) &&
      !ABI33_0_0YGFloatIsUndefined(size) && !ABI33_0_0YGFloatIsUndefined(lastComputedSize) &&
      lastSize > size &&
      (lastComputedSize <= size || ABI33_0_0YGFloatsEqual(size, lastComputedSize));
}

float ABI33_0_0YGRoundValueToPixelGrid(
    const float value,
    const float pointScaleFactor,
    const bool forceCeil,
    const bool forceFloor) {
  float scaledValue = value * pointScaleFactor;
  // We want to calculate `fractial` such that `floor(scaledValue) = scaledValue
  // - fractial`.
  float fractial = fmodf(scaledValue, 1.0f);
  if (fractial < 0) {
    // This branch is for handling negative numbers for `value`.
    //
    // Regarding `floor` and `ceil`. Note that for a number x, `floor(x) <= x <=
    // ceil(x)` even for negative numbers. Here are a couple of examples:
    //   - x =  2.2: floor( 2.2) =  2, ceil( 2.2) =  3
    //   - x = -2.2: floor(-2.2) = -3, ceil(-2.2) = -2
    //
    // Regarding `fmodf`. For fractional negative numbers, `fmodf` returns a
    // negative number. For example, `fmodf(-2.2) = -0.2`. However, we want
    // `fractial` to be the number such that subtracting it from `value` will
    // give us `floor(value)`. In the case of negative numbers, adding 1 to
    // `fmodf(value)` gives us this. Let's continue the example from above:
    //   - fractial = fmodf(-2.2) = -0.2
    //   - Add 1 to the fraction: fractial2 = fractial + 1 = -0.2 + 1 = 0.8
    //   - Finding the `floor`: -2.2 - fractial2 = -2.2 - 0.8 = -3
    ++fractial;
  }
  if (ABI33_0_0YGFloatsEqual(fractial, 0)) {
    // First we check if the value is already rounded
    scaledValue = scaledValue - fractial;
  } else if (ABI33_0_0YGFloatsEqual(fractial, 1.0f)) {
    scaledValue = scaledValue - fractial + 1.0f;
  } else if (forceCeil) {
    // Next we check if we need to use forced rounding
    scaledValue = scaledValue - fractial + 1.0f;
  } else if (forceFloor) {
    scaledValue = scaledValue - fractial;
  } else {
    // Finally we just round the value
    scaledValue = scaledValue - fractial +
        (!ABI33_0_0YGFloatIsUndefined(fractial) &&
                 (fractial > 0.5f || ABI33_0_0YGFloatsEqual(fractial, 0.5f))
             ? 1.0f
             : 0.0f);
  }
  return (ABI33_0_0YGFloatIsUndefined(scaledValue) ||
          ABI33_0_0YGFloatIsUndefined(pointScaleFactor))
      ? ABI33_0_0YGUndefined
      : scaledValue / pointScaleFactor;
}

bool ABI33_0_0YGNodeCanUseCachedMeasurement(
    const ABI33_0_0YGMeasureMode widthMode,
    const float width,
    const ABI33_0_0YGMeasureMode heightMode,
    const float height,
    const ABI33_0_0YGMeasureMode lastWidthMode,
    const float lastWidth,
    const ABI33_0_0YGMeasureMode lastHeightMode,
    const float lastHeight,
    const float lastComputedWidth,
    const float lastComputedHeight,
    const float marginRow,
    const float marginColumn,
    const ABI33_0_0YGConfigRef config) {
  if ((!ABI33_0_0YGFloatIsUndefined(lastComputedHeight) && lastComputedHeight < 0) ||
      (!ABI33_0_0YGFloatIsUndefined(lastComputedWidth) && lastComputedWidth < 0)) {
    return false;
  }
  bool useRoundedComparison =
      config != nullptr && config->pointScaleFactor != 0;
  const float effectiveWidth = useRoundedComparison
      ? ABI33_0_0YGRoundValueToPixelGrid(width, config->pointScaleFactor, false, false)
      : width;
  const float effectiveHeight = useRoundedComparison
      ? ABI33_0_0YGRoundValueToPixelGrid(height, config->pointScaleFactor, false, false)
      : height;
  const float effectiveLastWidth = useRoundedComparison
      ? ABI33_0_0YGRoundValueToPixelGrid(
            lastWidth, config->pointScaleFactor, false, false)
      : lastWidth;
  const float effectiveLastHeight = useRoundedComparison
      ? ABI33_0_0YGRoundValueToPixelGrid(
            lastHeight, config->pointScaleFactor, false, false)
      : lastHeight;

  const bool hasSameWidthSpec = lastWidthMode == widthMode &&
      ABI33_0_0YGFloatsEqual(effectiveLastWidth, effectiveWidth);
  const bool hasSameHeightSpec = lastHeightMode == heightMode &&
      ABI33_0_0YGFloatsEqual(effectiveLastHeight, effectiveHeight);

  const bool widthIsCompatible =
      hasSameWidthSpec ||
      ABI33_0_0YGMeasureModeSizeIsExactAndMatchesOldMeasuredSize(
          widthMode, width - marginRow, lastComputedWidth) ||
      ABI33_0_0YGMeasureModeOldSizeIsUnspecifiedAndStillFits(
          widthMode, width - marginRow, lastWidthMode, lastComputedWidth) ||
      ABI33_0_0YGMeasureModeNewMeasureSizeIsStricterAndStillValid(
          widthMode,
          width - marginRow,
          lastWidthMode,
          lastWidth,
          lastComputedWidth);

  const bool heightIsCompatible =
      hasSameHeightSpec ||
      ABI33_0_0YGMeasureModeSizeIsExactAndMatchesOldMeasuredSize(
          heightMode, height - marginColumn, lastComputedHeight) ||
      ABI33_0_0YGMeasureModeOldSizeIsUnspecifiedAndStillFits(
          heightMode,
          height - marginColumn,
          lastHeightMode,
          lastComputedHeight) ||
      ABI33_0_0YGMeasureModeNewMeasureSizeIsStricterAndStillValid(
          heightMode,
          height - marginColumn,
          lastHeightMode,
          lastHeight,
          lastComputedHeight);

  return widthIsCompatible && heightIsCompatible;
}

//
// This is a wrapper around the ABI33_0_0YGNodelayoutImpl function. It determines whether
// the layout request is redundant and can be skipped.
//
// Parameters:
//  Input parameters are the same as ABI33_0_0YGNodelayoutImpl (see above)
//  Return parameter is true if layout was performed, false if skipped
//
bool ABI33_0_0YGLayoutNodeInternal(
    const ABI33_0_0YGNodeRef node,
    const float availableWidth,
    const float availableHeight,
    const ABI33_0_0YGDirection ownerDirection,
    const ABI33_0_0YGMeasureMode widthMeasureMode,
    const ABI33_0_0YGMeasureMode heightMeasureMode,
    const float ownerWidth,
    const float ownerHeight,
    const bool performLayout,
    const char* reason,
    const ABI33_0_0YGConfigRef config,
    ABI33_0_0YGMarkerLayoutData& layoutMarkerData) {
  ABI33_0_0YGLayout* layout = &node->getLayout();

  gDepth++;

  const bool needToVisitNode =
      (node->isDirty() && layout->generationCount != gCurrentGenerationCount) ||
      layout->lastOwnerDirection != ownerDirection;

  if (needToVisitNode) {
    // Invalidate the cached results.
    layout->nextCachedMeasurementsIndex = 0;
    layout->cachedLayout.widthMeasureMode = (ABI33_0_0YGMeasureMode) -1;
    layout->cachedLayout.heightMeasureMode = (ABI33_0_0YGMeasureMode) -1;
    layout->cachedLayout.computedWidth = -1;
    layout->cachedLayout.computedHeight = -1;
  }

  ABI33_0_0YGCachedMeasurement* cachedResults = nullptr;

  // Determine whether the results are already cached. We maintain a separate
  // cache for layouts and measurements. A layout operation modifies the
  // positions and dimensions for nodes in the subtree. The algorithm assumes
  // that each node gets layed out a maximum of one time per tree layout, but
  // multiple measurements may be required to resolve all of the flex
  // dimensions. We handle nodes with measure functions specially here because
  // they are the most expensive to measure, so it's worth avoiding redundant
  // measurements if at all possible.
  if (node->getMeasure() != nullptr) {
    const float marginAxisRow =
        node->getMarginForAxis(ABI33_0_0YGFlexDirectionRow, ownerWidth).unwrap();
    const float marginAxisColumn =
        node->getMarginForAxis(ABI33_0_0YGFlexDirectionColumn, ownerWidth).unwrap();

    // First, try to use the layout cache.
    if (ABI33_0_0YGNodeCanUseCachedMeasurement(
            widthMeasureMode,
            availableWidth,
            heightMeasureMode,
            availableHeight,
            layout->cachedLayout.widthMeasureMode,
            layout->cachedLayout.availableWidth,
            layout->cachedLayout.heightMeasureMode,
            layout->cachedLayout.availableHeight,
            layout->cachedLayout.computedWidth,
            layout->cachedLayout.computedHeight,
            marginAxisRow,
            marginAxisColumn,
            config)) {
      cachedResults = &layout->cachedLayout;
    } else {
      // Try to use the measurement cache.
      for (uint32_t i = 0; i < layout->nextCachedMeasurementsIndex; i++) {
        if (ABI33_0_0YGNodeCanUseCachedMeasurement(
                widthMeasureMode,
                availableWidth,
                heightMeasureMode,
                availableHeight,
                layout->cachedMeasurements[i].widthMeasureMode,
                layout->cachedMeasurements[i].availableWidth,
                layout->cachedMeasurements[i].heightMeasureMode,
                layout->cachedMeasurements[i].availableHeight,
                layout->cachedMeasurements[i].computedWidth,
                layout->cachedMeasurements[i].computedHeight,
                marginAxisRow,
                marginAxisColumn,
                config)) {
          cachedResults = &layout->cachedMeasurements[i];
          break;
        }
      }
    }
  } else if (performLayout) {
    if (ABI33_0_0YGFloatsEqual(layout->cachedLayout.availableWidth, availableWidth) &&
        ABI33_0_0YGFloatsEqual(layout->cachedLayout.availableHeight, availableHeight) &&
        layout->cachedLayout.widthMeasureMode == widthMeasureMode &&
        layout->cachedLayout.heightMeasureMode == heightMeasureMode) {
      cachedResults = &layout->cachedLayout;
    }
  } else {
    for (uint32_t i = 0; i < layout->nextCachedMeasurementsIndex; i++) {
      if (ABI33_0_0YGFloatsEqual(
              layout->cachedMeasurements[i].availableWidth, availableWidth) &&
          ABI33_0_0YGFloatsEqual(
              layout->cachedMeasurements[i].availableHeight, availableHeight) &&
          layout->cachedMeasurements[i].widthMeasureMode == widthMeasureMode &&
          layout->cachedMeasurements[i].heightMeasureMode ==
              heightMeasureMode) {
        cachedResults = &layout->cachedMeasurements[i];
        break;
      }
    }
  }

  if (!needToVisitNode && cachedResults != nullptr) {
    layout->measuredDimensions[ABI33_0_0YGDimensionWidth] = cachedResults->computedWidth;
    layout->measuredDimensions[ABI33_0_0YGDimensionHeight] =
        cachedResults->computedHeight;

    (performLayout ? layoutMarkerData.cachedLayouts
                   : layoutMarkerData.cachedMeasures) += 1;

    if (gPrintChanges && gPrintSkips) {
      ABI33_0_0YGLog(
          node,
          ABI33_0_0YGLogLevelVerbose,
          "%s%d.{[skipped] ",
          ABI33_0_0YGSpacer(gDepth),
          gDepth);
      if (node->getPrintFunc() != nullptr) {
        node->getPrintFunc()(node);
      }
      ABI33_0_0YGLog(
          node,
          ABI33_0_0YGLogLevelVerbose,
          "wm: %s, hm: %s, aw: %f ah: %f => d: (%f, %f) %s\n",
          ABI33_0_0YGMeasureModeName(widthMeasureMode, performLayout),
          ABI33_0_0YGMeasureModeName(heightMeasureMode, performLayout),
          availableWidth,
          availableHeight,
          cachedResults->computedWidth,
          cachedResults->computedHeight,
          reason);
    }
  } else {
    if (gPrintChanges) {
      ABI33_0_0YGLog(
          node,
          ABI33_0_0YGLogLevelVerbose,
          "%s%d.{%s",
          ABI33_0_0YGSpacer(gDepth),
          gDepth,
          needToVisitNode ? "*" : "");
      if (node->getPrintFunc() != nullptr) {
        node->getPrintFunc()(node);
      }
      ABI33_0_0YGLog(
          node,
          ABI33_0_0YGLogLevelVerbose,
          "wm: %s, hm: %s, aw: %f ah: %f %s\n",
          ABI33_0_0YGMeasureModeName(widthMeasureMode, performLayout),
          ABI33_0_0YGMeasureModeName(heightMeasureMode, performLayout),
          availableWidth,
          availableHeight,
          reason);
    }

    ABI33_0_0YGNodelayoutImpl(
        node,
        availableWidth,
        availableHeight,
        ownerDirection,
        widthMeasureMode,
        heightMeasureMode,
        ownerWidth,
        ownerHeight,
        performLayout,
        config,
        layoutMarkerData);

    if (gPrintChanges) {
      ABI33_0_0YGLog(
          node,
          ABI33_0_0YGLogLevelVerbose,
          "%s%d.}%s",
          ABI33_0_0YGSpacer(gDepth),
          gDepth,
          needToVisitNode ? "*" : "");
      if (node->getPrintFunc() != nullptr) {
        node->getPrintFunc()(node);
      }
      ABI33_0_0YGLog(
          node,
          ABI33_0_0YGLogLevelVerbose,
          "wm: %s, hm: %s, d: (%f, %f) %s\n",
          ABI33_0_0YGMeasureModeName(widthMeasureMode, performLayout),
          ABI33_0_0YGMeasureModeName(heightMeasureMode, performLayout),
          layout->measuredDimensions[ABI33_0_0YGDimensionWidth],
          layout->measuredDimensions[ABI33_0_0YGDimensionHeight],
          reason);
    }

    layout->lastOwnerDirection = ownerDirection;

    if (cachedResults == nullptr) {
      if (layout->nextCachedMeasurementsIndex + 1 >
          (uint32_t) layoutMarkerData.maxMeasureCache) {
        layoutMarkerData.maxMeasureCache =
            layout->nextCachedMeasurementsIndex + 1;
      }
      if (layout->nextCachedMeasurementsIndex == ABI33_0_0YG_MAX_CACHED_RESULT_COUNT) {
        if (gPrintChanges) {
          ABI33_0_0YGLog(node, ABI33_0_0YGLogLevelVerbose, "Out of cache entries!\n");
        }
        layout->nextCachedMeasurementsIndex = 0;
      }

      ABI33_0_0YGCachedMeasurement* newCacheEntry;
      if (performLayout) {
        // Use the single layout cache entry.
        newCacheEntry = &layout->cachedLayout;
      } else {
        // Allocate a new measurement cache entry.
        newCacheEntry =
            &layout->cachedMeasurements[layout->nextCachedMeasurementsIndex];
        layout->nextCachedMeasurementsIndex++;
      }

      newCacheEntry->availableWidth = availableWidth;
      newCacheEntry->availableHeight = availableHeight;
      newCacheEntry->widthMeasureMode = widthMeasureMode;
      newCacheEntry->heightMeasureMode = heightMeasureMode;
      newCacheEntry->computedWidth =
          layout->measuredDimensions[ABI33_0_0YGDimensionWidth];
      newCacheEntry->computedHeight =
          layout->measuredDimensions[ABI33_0_0YGDimensionHeight];
    }
  }

  if (performLayout) {
    node->setLayoutDimension(
        node->getLayout().measuredDimensions[ABI33_0_0YGDimensionWidth],
        ABI33_0_0YGDimensionWidth);
    node->setLayoutDimension(
        node->getLayout().measuredDimensions[ABI33_0_0YGDimensionHeight],
        ABI33_0_0YGDimensionHeight);

    node->setHasNewLayout(true);
    node->setDirty(false);
  }

  gDepth--;
  layout->generationCount = gCurrentGenerationCount;
  return (needToVisitNode || cachedResults == nullptr);
}

void ABI33_0_0YGConfigSetPointScaleFactor(
    const ABI33_0_0YGConfigRef config,
    const float pixelsInPoint) {
  ABI33_0_0YGAssertWithConfig(
      config,
      pixelsInPoint >= 0.0f,
      "Scale factor should not be less than zero");

  // We store points for Pixel as we will use it for rounding
  if (pixelsInPoint == 0.0f) {
    // Zero is used to skip rounding
    config->pointScaleFactor = 0.0f;
  } else {
    config->pointScaleFactor = pixelsInPoint;
  }
}

static void ABI33_0_0YGRoundToPixelGrid(
    const ABI33_0_0YGNodeRef node,
    const float pointScaleFactor,
    const float absoluteLeft,
    const float absoluteTop) {
  if (pointScaleFactor == 0.0f) {
    return;
  }

  const float nodeLeft = node->getLayout().position[ABI33_0_0YGEdgeLeft];
  const float nodeTop = node->getLayout().position[ABI33_0_0YGEdgeTop];

  const float nodeWidth = node->getLayout().dimensions[ABI33_0_0YGDimensionWidth];
  const float nodeHeight = node->getLayout().dimensions[ABI33_0_0YGDimensionHeight];

  const float absoluteNodeLeft = absoluteLeft + nodeLeft;
  const float absoluteNodeTop = absoluteTop + nodeTop;

  const float absoluteNodeRight = absoluteNodeLeft + nodeWidth;
  const float absoluteNodeBottom = absoluteNodeTop + nodeHeight;

  // If a node has a custom measure function we never want to round down its
  // size as this could lead to unwanted text truncation.
  const bool textRounding = node->getNodeType() == ABI33_0_0YGNodeTypeText;

  node->setLayoutPosition(
      ABI33_0_0YGRoundValueToPixelGrid(nodeLeft, pointScaleFactor, false, textRounding),
      ABI33_0_0YGEdgeLeft);

  node->setLayoutPosition(
      ABI33_0_0YGRoundValueToPixelGrid(nodeTop, pointScaleFactor, false, textRounding),
      ABI33_0_0YGEdgeTop);

  // We multiply dimension by scale factor and if the result is close to the
  // whole number, we don't have any fraction To verify if the result is close
  // to whole number we want to check both floor and ceil numbers
  const bool hasFractionalWidth =
      !ABI33_0_0YGFloatsEqual(fmodf(nodeWidth * pointScaleFactor, 1.0), 0) &&
      !ABI33_0_0YGFloatsEqual(fmodf(nodeWidth * pointScaleFactor, 1.0), 1.0);
  const bool hasFractionalHeight =
      !ABI33_0_0YGFloatsEqual(fmodf(nodeHeight * pointScaleFactor, 1.0), 0) &&
      !ABI33_0_0YGFloatsEqual(fmodf(nodeHeight * pointScaleFactor, 1.0), 1.0);

  node->setLayoutDimension(
      ABI33_0_0YGRoundValueToPixelGrid(
          absoluteNodeRight,
          pointScaleFactor,
          (textRounding && hasFractionalWidth),
          (textRounding && !hasFractionalWidth)) -
          ABI33_0_0YGRoundValueToPixelGrid(
              absoluteNodeLeft, pointScaleFactor, false, textRounding),
      ABI33_0_0YGDimensionWidth);

  node->setLayoutDimension(
      ABI33_0_0YGRoundValueToPixelGrid(
          absoluteNodeBottom,
          pointScaleFactor,
          (textRounding && hasFractionalHeight),
          (textRounding && !hasFractionalHeight)) -
          ABI33_0_0YGRoundValueToPixelGrid(
              absoluteNodeTop, pointScaleFactor, false, textRounding),
      ABI33_0_0YGDimensionHeight);

  const uint32_t childCount = ABI33_0_0YGNodeGetChildCount(node);
  for (uint32_t i = 0; i < childCount; i++) {
    ABI33_0_0YGRoundToPixelGrid(
        ABI33_0_0YGNodeGetChild(node, i),
        pointScaleFactor,
        absoluteNodeLeft,
        absoluteNodeTop);
  }
}

void ABI33_0_0YGNodeCalculateLayout(
    const ABI33_0_0YGNodeRef node,
    const float ownerWidth,
    const float ownerHeight,
    const ABI33_0_0YGDirection ownerDirection) {
  marker::MarkerSection<ABI33_0_0YGMarkerLayout> marker{node};

  // Increment the generation count. This will force the recursive routine to
  // visit all dirty nodes at least once. Subsequent visits will be skipped if
  // the input parameters don't change.
  gCurrentGenerationCount++;
  node->resolveDimension();
  float width = ABI33_0_0YGUndefined;
  ABI33_0_0YGMeasureMode widthMeasureMode = ABI33_0_0YGMeasureModeUndefined;
  if (ABI33_0_0YGNodeIsStyleDimDefined(node, ABI33_0_0YGFlexDirectionRow, ownerWidth)) {
    width =
        (ABI33_0_0YGResolveValue(
             node->getResolvedDimension(dim[ABI33_0_0YGFlexDirectionRow]), ownerWidth) +
         node->getMarginForAxis(ABI33_0_0YGFlexDirectionRow, ownerWidth))
            .unwrap();
    widthMeasureMode = ABI33_0_0YGMeasureModeExactly;
  } else if (!ABI33_0_0YGResolveValue(
                  node->getStyle().maxDimensions[ABI33_0_0YGDimensionWidth], ownerWidth)
                  .isUndefined()) {
    width = ABI33_0_0YGResolveValue(
                node->getStyle().maxDimensions[ABI33_0_0YGDimensionWidth], ownerWidth)
                .unwrap();
    widthMeasureMode = ABI33_0_0YGMeasureModeAtMost;
  } else {
    width = ownerWidth;
    widthMeasureMode = ABI33_0_0YGFloatIsUndefined(width) ? ABI33_0_0YGMeasureModeUndefined
                                                 : ABI33_0_0YGMeasureModeExactly;
  }

  float height = ABI33_0_0YGUndefined;
  ABI33_0_0YGMeasureMode heightMeasureMode = ABI33_0_0YGMeasureModeUndefined;
  if (ABI33_0_0YGNodeIsStyleDimDefined(node, ABI33_0_0YGFlexDirectionColumn, ownerHeight)) {
    height = (ABI33_0_0YGResolveValue(
                  node->getResolvedDimension(dim[ABI33_0_0YGFlexDirectionColumn]),
                  ownerHeight) +
              node->getMarginForAxis(ABI33_0_0YGFlexDirectionColumn, ownerWidth))
                 .unwrap();
    heightMeasureMode = ABI33_0_0YGMeasureModeExactly;
  } else if (!ABI33_0_0YGResolveValue(
                  node->getStyle().maxDimensions[ABI33_0_0YGDimensionHeight],
                  ownerHeight)
                  .isUndefined()) {
    height = ABI33_0_0YGResolveValue(
                 node->getStyle().maxDimensions[ABI33_0_0YGDimensionHeight], ownerHeight)
                 .unwrap();
    heightMeasureMode = ABI33_0_0YGMeasureModeAtMost;
  } else {
    height = ownerHeight;
    heightMeasureMode = ABI33_0_0YGFloatIsUndefined(height) ? ABI33_0_0YGMeasureModeUndefined
                                                   : ABI33_0_0YGMeasureModeExactly;
  }
  if (ABI33_0_0YGLayoutNodeInternal(
          node,
          width,
          height,
          ownerDirection,
          widthMeasureMode,
          heightMeasureMode,
          ownerWidth,
          ownerHeight,
          true,
          "initial",
          node->getConfig(),
          marker.data)) {
    node->setPosition(
        node->getLayout().direction, ownerWidth, ownerHeight, ownerWidth);
    ABI33_0_0YGRoundToPixelGrid(node, node->getConfig()->pointScaleFactor, 0.0f, 0.0f);

    if (node->getConfig()->printTree) {
      ABI33_0_0YGNodePrint(
          node,
          (ABI33_0_0YGPrintOptions)(
              ABI33_0_0YGPrintOptionsLayout | ABI33_0_0YGPrintOptionsChildren |
              ABI33_0_0YGPrintOptionsStyle));
    }
  }

  // We want to get rid off `useLegacyStretchBehaviour` from ABI33_0_0YGConfig. But we
  // aren't sure whether client's of ABI33_0_0yoga have gotten rid off this flag or not.
  // So logging this in ABI33_0_0YGLayout would help to find out the call sites depending
  // on this flag. This check would be removed once we are sure no one is
  // dependent on this flag anymore. The flag
  // `shouldDiffLayoutWithoutLegacyStretchBehaviour` in ABI33_0_0YGConfig will help to
  // run experiments.
  if (node->getConfig()->shouldDiffLayoutWithoutLegacyStretchBehaviour &&
      node->didUseLegacyFlag()) {
    const ABI33_0_0YGNodeRef originalNode = ABI33_0_0YGNodeDeepClone(node);
    originalNode->resolveDimension();
    // Recursively mark nodes as dirty
    originalNode->markDirtyAndPropogateDownwards();
    gCurrentGenerationCount++;
    // Rerun the layout, and calculate the diff
    originalNode->setAndPropogateUseLegacyFlag(false);
    ABI33_0_0YGMarkerLayoutData layoutMarkerData;
    if (ABI33_0_0YGLayoutNodeInternal(
            originalNode,
            width,
            height,
            ownerDirection,
            widthMeasureMode,
            heightMeasureMode,
            ownerWidth,
            ownerHeight,
            true,
            "initial",
            originalNode->getConfig(),
            layoutMarkerData)) {
      originalNode->setPosition(
          originalNode->getLayout().direction,
          ownerWidth,
          ownerHeight,
          ownerWidth);
      ABI33_0_0YGRoundToPixelGrid(
          originalNode,
          originalNode->getConfig()->pointScaleFactor,
          0.0f,
          0.0f);

      // Set whether the two layouts are different or not.
      auto neededLegacyStretchBehaviour =
          !originalNode->isLayoutTreeEqualToNode(*node);
      node->setLayoutDoesLegacyFlagAffectsLayout(neededLegacyStretchBehaviour);

      if (originalNode->getConfig()->printTree) {
        ABI33_0_0YGNodePrint(
            originalNode,
            (ABI33_0_0YGPrintOptions)(
                ABI33_0_0YGPrintOptionsLayout | ABI33_0_0YGPrintOptionsChildren |
                ABI33_0_0YGPrintOptionsStyle));
      }
    }
    ABI33_0_0YGConfigFreeRecursive(originalNode);
    ABI33_0_0YGNodeFreeRecursive(originalNode);
  }
}

void ABI33_0_0YGConfigSetLogger(const ABI33_0_0YGConfigRef config, ABI33_0_0YGLogger logger) {
  if (logger != nullptr) {
    config->logger = logger;
  } else {
#ifdef ANDROID
    config->logger = &ABI33_0_0YGAndroidLog;
#else
    config->logger = &ABI33_0_0YGDefaultLog;
#endif
  }
}

void ABI33_0_0YGConfigSetShouldDiffLayoutWithoutLegacyStretchBehaviour(
    const ABI33_0_0YGConfigRef config,
    const bool shouldDiffLayout) {
  config->shouldDiffLayoutWithoutLegacyStretchBehaviour = shouldDiffLayout;
}

static void ABI33_0_0YGVLog(
    const ABI33_0_0YGConfigRef config,
    const ABI33_0_0YGNodeRef node,
    ABI33_0_0YGLogLevel level,
    const char* format,
    va_list args) {
  const ABI33_0_0YGConfigRef logConfig =
      config != nullptr ? config : ABI33_0_0YGConfigGetDefault();
  logConfig->logger(logConfig, node, level, format, args);

  if (level == ABI33_0_0YGLogLevelFatal) {
    abort();
  }
}

void ABI33_0_0YGLogWithConfig(
    const ABI33_0_0YGConfigRef config,
    ABI33_0_0YGLogLevel level,
    const char* format,
    ...) {
  va_list args;
  va_start(args, format);
  ABI33_0_0YGVLog(config, nullptr, level, format, args);
  va_end(args);
}

void ABI33_0_0YGLog(const ABI33_0_0YGNodeRef node, ABI33_0_0YGLogLevel level, const char* format, ...) {
  va_list args;
  va_start(args, format);
  ABI33_0_0YGVLog(
      node == nullptr ? nullptr : node->getConfig(), node, level, format, args);
  va_end(args);
}

void ABI33_0_0YGAssert(const bool condition, const char* message) {
  if (!condition) {
    ABI33_0_0YGLog(nullptr, ABI33_0_0YGLogLevelFatal, "%s\n", message);
  }
}

void ABI33_0_0YGAssertWithNode(
    const ABI33_0_0YGNodeRef node,
    const bool condition,
    const char* message) {
  if (!condition) {
    ABI33_0_0YGLog(node, ABI33_0_0YGLogLevelFatal, "%s\n", message);
  }
}

void ABI33_0_0YGAssertWithConfig(
    const ABI33_0_0YGConfigRef config,
    const bool condition,
    const char* message) {
  if (!condition) {
    ABI33_0_0YGLogWithConfig(config, ABI33_0_0YGLogLevelFatal, "%s\n", message);
  }
}

void ABI33_0_0YGConfigSetExperimentalFeatureEnabled(
    const ABI33_0_0YGConfigRef config,
    const ABI33_0_0YGExperimentalFeature feature,
    const bool enabled) {
  config->experimentalFeatures[feature] = enabled;
}

inline bool ABI33_0_0YGConfigIsExperimentalFeatureEnabled(
    const ABI33_0_0YGConfigRef config,
    const ABI33_0_0YGExperimentalFeature feature) {
  return config->experimentalFeatures[feature];
}

void ABI33_0_0YGConfigSetUseWebDefaults(const ABI33_0_0YGConfigRef config, const bool enabled) {
  config->useWebDefaults = enabled;
}

void ABI33_0_0YGConfigSetUseLegacyStretchBehaviour(
    const ABI33_0_0YGConfigRef config,
    const bool useLegacyStretchBehaviour) {
  config->useLegacyStretchBehaviour = useLegacyStretchBehaviour;
}

bool ABI33_0_0YGConfigGetUseWebDefaults(const ABI33_0_0YGConfigRef config) {
  return config->useWebDefaults;
}

void ABI33_0_0YGConfigSetContext(const ABI33_0_0YGConfigRef config, void* context) {
  config->context = context;
}

void* ABI33_0_0YGConfigGetContext(const ABI33_0_0YGConfigRef config) {
  return config->context;
}

void ABI33_0_0YGConfigSetCloneNodeFunc(
    const ABI33_0_0YGConfigRef config,
    const ABI33_0_0YGCloneNodeFunc callback) {
  config->cloneNodeCallback = callback;
}

static void ABI33_0_0YGTraverseChildrenPreOrder(
    const ABI33_0_0YGVector& children,
    const std::function<void(ABI33_0_0YGNodeRef node)>& f) {
  for (ABI33_0_0YGNodeRef node : children) {
    f(node);
    ABI33_0_0YGTraverseChildrenPreOrder(node->getChildren(), f);
  }
}

void ABI33_0_0YGTraversePreOrder(
    ABI33_0_0YGNodeRef const node,
    std::function<void(ABI33_0_0YGNodeRef node)>&& f) {
  if (!node) {
    return;
  }
  f(node);
  ABI33_0_0YGTraverseChildrenPreOrder(node->getChildren(), f);
}
