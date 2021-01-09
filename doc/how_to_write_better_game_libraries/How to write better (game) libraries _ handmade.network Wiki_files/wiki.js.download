
document.addEventListener("DOMContentLoaded", function(){
    asides = getElementsByClass(document, "aside");
    for (var i = 0; i < asides.length; ++i)
    {
        var aside = asides[i];
        addClass(aside, "folded");
        button = getElementsByClass(aside, "aside-heading")[0];
        button.addEventListener("click", function(aside) { 
            return function(evt, target) {
                toggleClass(aside, "folded");
            }
        }(aside));
    }
});
