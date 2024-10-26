include $(TOPDIR)/rules.mk
PKG_NAME:=libtuya
PKG_RELEASE:=1
PKG_VERSION:=1.0.0
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/tuya/tuya-iot-core-sdk.git
PKG_SOURCE_VERSION:=0208badefb2003d30e70b5b875395e3187c850d9
CMAKE_BINARY_SUBDIR:=build

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/$(PKG_NAME)
	CATEGORY:=Libraries
	TITLE:=libtuya
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib $(1)/usr/include
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/examples/data_model_basic_demo/tuya_cacert.h $(1)/usr/include
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/lib/*.so $(1)/usr/lib/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/include/*h $(1)/usr/include/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/middleware/*h $(1)/usr/include/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/utils/*h $(1)/usr/include/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/interface/* $(1)/usr/include/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/libraries/coreHTTP/source/include/*h $(1)/usr/include
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/libraries/coreHTTP/source/dependency/3rdparty/http_parser/*h $(1)/usr/include
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/libraries/coreJSON/source/include/*h $(1)/usr/include
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/libraries/coreMQTT/source/include/*h $(1)/usr/include
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/libraries/mbedtls/include/mbedtls/*h $(1)/usr/include
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/build/lib/*.so $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libtuya))
