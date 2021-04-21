include $(TOPDIR)/rules.mk

# Name, version and release number
# The name and version of your package are used to define the variable to point to the build directory of your package: $(PKG_BUILD_DIR)
PKG_NAME:=routerInterface
PKG_VERSION:=1.0
PKG_RELEASE:=1

# Source settings (i.e. where to find the source codes)
# This is a custom variable, used below
SOURCE_DIR:=/home/deyo2303/buildroot/routerInterface/Debug/src
CPP_DIR:=/home/deyo2303/buildroot/routerInterface/src
H_DIR:=/home/deyo2303/buildroot/routerInterface/include
RC_DIR:/home/deyo2303/buildroot/routerInterface/Debug

include $(INCLUDE_DIR)/package.mk

# Package definition; instructs on how and where our package will appear in the overall configuration menu ('make menuconfig')
define Package/routerInterface
  SECTION:=examples
  CATEGORY:=Examples
  TITLE:=Router Interface
  DEPENDS:=+libstdcpp +libc
endef

#+USE_GLIBC:librt +USE_GLIBC:libpthread
# Package description; a more verbose description on what our package does
define Package/routerInterface/description
  A router interface -application.
endef

# Package preparation instructions; create the build directory and copy the source code. 
# The last command is necessary to ensure our preparation instructions remain compatible with the patching system.
define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	mkdir -p $(PKG_BUILD_DIR)/include
	mkdir -p $(PKG_BUILD_DIR)/src
	cp --recursive $(SOURCE_DIR)/* $(PKG_BUILD_DIR)
	cp --recursive $(CPP_DIR)/*.cpp $(PKG_BUILD_DIR)/src
	cp --recursive $(H_DIR)/*.h $(PKG_BUILD_DIR)/include
	cp $(RC_DIR)/*.txt $(PKG_BUILD_DIR)
	$(Build/Patch)
endef

# Package build instructions; invoke the target-specific compiler to first compile the source file, and then to link the file into the final executable
define Build/Compile
#$(TARGET_CC) $(TARGET_CFLAGS) -o $(PKG_BUILD_DIR)/routerInterface.o -cpp $(PKG_BUILD_DIR)/startup.cpp
#$(TARGET_CC) $(TARGET_LDFLAGS) -o $(PKG_BUILD_DIR)/$1 $(PKG_BUILD_DIR)/routerInterface.o
	$(TARGET_CXX)    -c -o $(PKG_BUILD_DIR)/configUtil.o $(PKG_BUILD_DIR)/src/configUtil.cpp
	$(TARGET_CXX)    -c -o $(PKG_BUILD_DIR)/helloMulticast.o $(PKG_BUILD_DIR)/src/helloMulticast.cpp
	$(TARGET_CXX)    -c -o $(PKG_BUILD_DIR)/helloPacket.o $(PKG_BUILD_DIR)/src/helloPacket.cpp
	$(TARGET_CXX) -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(PKG_BUILD_DIR)/edge.d" -MT"$(PKG_BUILD_DIR)/edge.o" -o "$(PKG_BUILD_DIR)/edge.o" "$(PKG_BUILD_DIR)/src/edge.cpp"
	$(TARGET_CXX) -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(PKG_BUILD_DIR)/graph.d" -MT"$(PKG_BUILD_DIR)/graph.o" -o "$(PKG_BUILD_DIR)/graph.o" "$(PKG_BUILD_DIR)/src/graph.cpp"
	$(TARGET_CXX) -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(PKG_BUILD_DIR)/hNode.d" -MT"$(PKG_BUILD_DIR)/hNode.o" -o "$(PKG_BUILD_DIR)/hNode.o" "$(PKG_BUILD_DIR)/src/hNode.cpp"
	$(TARGET_CXX) -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(PKG_BUILD_DIR)/startup.d" -MT"$(PKG_BUILD_DIR)/startup.o" -o "$(PKG_BUILD_DIR)/startup.o" "$(PKG_BUILD_DIR)/src/startup.cpp"
	$(TARGET_CXX)  -o $(PKG_BUILD_DIR)/$1  $(PKG_BUILD_DIR)/configUtil.o $(PKG_BUILD_DIR)/helloMulticast.o $(PKG_BUILD_DIR)/helloPacket.o $(PKG_BUILD_DIR)/edge.o $(PKG_BUILD_DIR)/graph.o $(PKG_BUILD_DIR)/hNode.o $(PKG_BUILD_DIR)/startup.o   -lpthread
endef

# Package install instructions; create a directory inside the package to hold our executable, and then copy the executable we built previously into the folder
define Package/routerInterface/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/routerInterface $(1)/usr/bin
endef

# This command is always the last, it uses the definitions and variables we give above in order to get the job done
$(eval $(call BuildPackage,routerInterface))
