/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

void cdma_properties(char const default_cdma_sub[], char const default_network[])
{
    property_set("ro.telephony.default_cdma_sub", default_cdma_sub);
    property_set("ro.telephony.default_network", default_network);

    property_set("telephony.lteOnCdmaDevice", "1");
    property_set("ro.ril.svdo", "true");
    property_set("ro.ril.disable.fd.plmn.prefix", "23402,23410,23411,23420");
    property_set("ro.ril.enable.sdr", "0");
    property_set("ro.ril.enable.gea3", "1");
    property_set("ro.ril.enable.a53", "1");
    property_set("persist.radio.snapshot_enabled", "1");
    property_set("persist.radio.snapshot_timer", "22");
}

void gsm_properties(char const default_network[])
{
    property_set("ro.telephony.default_network", default_network);
    property_set("ro.ril.hsupa.category", "6");
    property_set("ro.ril.hsxpa", "4");
    property_set("ro.ril.disable.cpc", "1");
    property_set("ro.ril.enable.pre_r8fd", "1");
    property_set("ro.ril.enable.sdr", "1");
    property_set("ro.ril.enable.r8fd", "1");
    property_set("ro.ril.disable.fd.plmn.prefix", "23402,23410,23411,23420,23594,27202,27205");
}

void init_msm_properties(unsigned long msm_id, unsigned long msm_ver, char *board_type)
{
    char platform[PROP_VALUE_MAX];
    char bootmid[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    int rc;

    rc = property_get("ro.board.platform", platform);
    if (!rc || strncmp(platform, ANDROID_TARGET, PROP_VALUE_MAX))
        return;

    property_get("ro.boot.mid", bootmid);

    if (strstr(bootmid, "0P9C10000")) {
        /* a5tl */
        gsm_properties("9");
        property_set("ro.build.fingerprint", "htc/htccn_chs_cmcc/htc_a5tl:4.4.2/KOT49H/391137.3:user/release-keys");
        property_set("ro.build.description", "2.07.1403.3 CL391137 release-keys");
        property_set("ro.product.model", "D816t");
        property_set("ro.product.device", "htc_a5tl");
        property_set("ro.build.product", "htc_a5tl");
        property_set("ro.ril.hsdpa.category", "10");
        property_set("ro.ril.hsxpa", "2");
        property_set("ro.ril.enable.sdr", "0");
        property_set("ro.ril.enable.a53", "1");
        property_set("ro.ril.disable.fd.plmn.prefix", "23402,23410,23411,23420,27202");
        property_set("ro.ril.oem.ecclist", "112,000,08,110,118,119,911,999,120,122");
        property_set("ro.ril.set.mtusize", "1420");
    } else if (strstr(bootmid, "0P9C30000")) {
        /* a5chl */
        cdma_properties("1", "8");
        property_set("ro.build.fingerprint", "htc/sprint_wwe_vm/htc_a5chl:5.0.2/LRX22G/510432.2:user/release-keys");
        property_set("ro.build.description", "2.33.652.2 CL510432 release-keys");
        property_set("ro.product.model", "710C");
        property_set("ro.product.device", "htc_a5chl");
        property_set("ro.build.product", "htc_a5chl");
        property_set("ro.ril.oem.ecclist", "911");
        property_set("ro.ril.set.mtusize", "1422");
        property_set("ro.cdma.home.operator.numeric", "310120");
        property_set("gsm.sim.operator.numeric", "310120");
        property_set("gsm.operator.numeric", "310120");
        property_set("ro.cdma.home.operator.alpha", "Sprint");
        property_set("gsm.sim.operator.alpha", "Sprint");
        property_set("gsm.operator.alpha", "310120");
        property_set("ro.telephony.ril_class", "a5sprRIL");
    } else {
        /* a5ul */
        gsm_properties("9");
        property_set("ro.build.fingerprint", "htc/htc_asia_wwe/htc_a5ul:4.4.2/KOT49H/358649.1:user/release-keys");
        property_set("ro.build.description", "1.49.707.1 CL358649 release-keys");
        property_set("ro.product.model", "Desire 816");
        property_set("ro.product.device", "htc_a5ul");
        property_set("ro.build.product", "htc_a5ul");
        property_set("ro.ril.hsdpa.category", "14");
        property_set("ro.ril.air.enabled", "1");
        property_set("ro.ril.enable.a53", "1");
        property_set("persist.radio.jbims", "1");
        property_set("ro.ril.enable.gea3", "1");
        property_set("ro.ril.gsm.to.lte.blind.redir", "1");
    }

    property_get("ro.product.device", device);
    ERROR("Found bootmid %s setting build properties for %s device\n", bootmid, device);
}
