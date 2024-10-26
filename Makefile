include $(TOPDIR)/rules.mk

PKG_NAME:=TuyaESPControl
PKG_VERSION:=1.0
PKG_RELEASE:=1
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_BUILD_DEPENDS:=!USE_GLIBC:argp-standalone

include $(INCLUDE_DIR)/package.mk

define Package/TuyaESPControl
	DEPENDS:=+libjson-c +libtuya +libubus +libubox +libblobmsg-json +libserialport
	CATEGORY:=Base system
	TITLE:=UBUS module for controlling ESP micro controller
endef

ifndef CONFIG_USE_GLIBC
	CONFIGURE_VARS += LIBS="-largp"
endif

define Package/TuyaESPControl/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tuya_esp $(1)/usr/bin/tuya_esp
	$(INSTALL_BIN) ./files/tuya_esp.init $(1)/etc/init.d/tuya_esp
endef

$(eval $(call BuildPackage,TuyaESPControl))
