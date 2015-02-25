CC=emcc

SOURCES=../source/spine/Animation.c \
../source/spine/AnimationState.c \
../source/spine/AnimationStateData.c \
../source/spine/Atlas.c \
../source/spine/AtlasAttachmentLoader.c \
../source/spine/Attachment.c \
../source/spine/AttachmentLoader.c \
../source/spine/Bone.c \
../source/spine/BoneData.c \
../source/spine/BoundingBoxAttachment.c \
../source/spine/Event.c \
../source/spine/EventData.c \
../source/spine/extension.c \
../source/spine/IkConstraint.c \
../source/spine/IkConstraintData.c \
../source/spine/Json.c \
../source/spine/MeshAttachment.c \
../source/spine/RegionAttachment.c \
../source/spine/Skeleton.c \
../source/spine/SkeletonBounds.c \
../source/spine/SkeletonData.c \
../source/spine/SkeletonJson.c \
../source/spine/Skin.c \
../source/spine/SkinnedMeshAttachment.c \
../source/spine/Slot.c \
../source/spine/SlotData.c

EXPORTS_FILE=makefile_exprots.txt

LOCAL_C_FLAGS=-Werror -std=c++11

LOCAL_C_INCLUDES=

OUTPUT=libSpine.bc

all: $(SOURCES) $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(SOURCES) -s EXPORTED_FUNCTIONS=@$(EXPORTS_FILE) $(LOCAL_C_FLAGS) $(LOCAL_C_INCLUDES) -o ../../../bin/$(OUTPUT)

