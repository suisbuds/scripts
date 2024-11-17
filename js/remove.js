// remove paste preventing on HUST online platform

(function() {
    'use strict';
    $(function() {
        setTimeout(() => {
            $("body").removeAttr("onselectstart");
            $("html").css("user-select", "unset");

            UE.EventBase.prototype.fireEvent = function(type, ...args) {
                if (type === 'paste') {
                    return null;
                }
            };
        }, 1000);
    });
})();