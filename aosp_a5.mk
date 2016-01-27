$(call inherit-product, device/htc/a5/full_a5.mk)

# Inherit some common AOSP stuff.
$(call inherit-product, vendor/aosp/common.mk)

# Device naming
PRODUCT_RELEASE_NAME := DESIRE 816
PRODUCT_NAME := aosp_a5

PRODUCT_GMS_CLIENTID_BASE := android-htc