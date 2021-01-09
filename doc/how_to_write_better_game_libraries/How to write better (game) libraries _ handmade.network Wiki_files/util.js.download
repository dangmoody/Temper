function containsClass(element, match)
{
    return (" " + element.className + " ").indexOf(" " + match + " ") > -1;
}

function removeClass(element, match)
{
    var paddedClass = " " + element.className + " ";
    var removed = paddedClass.replace(" "+match+" ", " ");
    element.className = removed;
}

function addClass(element, match)
{
    element.className = element.className + " " + match;
}

function toggleClass(element, match) {
    if (containsClass(element, match)) {
        removeClass(element, match);
    } else {
        addClass(element, match);
    }
}

function getElementsByClass(element, match)
{
    var result = [];
    var elems = element.getElementsByTagName("*");
    for (var i in elems) {
        if(containsClass(elems[i], match)){
            result.push(elems[i]);
        }
    }
    return result;
}

function getChildById(element, childID)
{
    var retElement = null;
    var lstChildren = element.children;

    for (var i = 0; i < lstChildren.length; i++)
    {
        if (lstChildren[i].id == childID)
        {
            retElement = lstChildren[i];
            break;
        }
        else if (arguments[2] === true)
        { 
            retElement = getChildById(lstChildren[i], childID, true); 
            if (retElement != null) { break; }
        }
    }

    return retElement;
}

function cloneNodeTree(node)
{
    if (node.cloneNode !== undefined)
    {
        var dup = node.cloneNode();
        for (var i = 0; i < node.childNodes.length; i++)
        {
            dup.appendChild(cloneNodeTree(node.childNodes[i]));
        }
        return dup;
    }
    // Problems
    return node;
}

// From http://stackoverflow.com/questions/263743/caret-position-in-textarea-in-characters-from-the-start
// Thanks to Tim Down for this code
function getSelectionRange(el) {
    var start = 0, end = 0, normalizedValue, range,
        textInputRange, len, endRange;

    if (typeof el.selectionStart == "number" && typeof el.selectionEnd == "number") {
        start = el.selectionStart;
        end = el.selectionEnd;
    } else {
        range = document.selection.createRange();

        if (range && range.parentElement() == el) {
            len = el.value.length;
            normalizedValue = el.value.replace(/\r\n/g, "\n");

            // Create a working TextRange that lives only in the input
            textInputRange = el.createTextRange();
            textInputRange.moveToBookmark(range.getBookmark());

            // Check if the start and end of the selection are at the very end
            // of the input, since moveStart/moveEnd doesn't return what we want
            // in those cases
            endRange = el.createTextRange();
            endRange.collapse(false);

            if (textInputRange.compareEndPoints("StartToEnd", endRange) > -1) {
                start = end = len;
            } else {
                start = -textInputRange.moveStart("character", -len);
                start += normalizedValue.slice(0, start).split("\n").length - 1;

                if (textInputRange.compareEndPoints("EndToEnd", endRange) > -1) {
                    end = len;
                } else {
                    end = -textInputRange.moveEnd("character", -len);
                    end += normalizedValue.slice(0, end).split("\n").length - 1;
                }
            }
        }
    }

    return {
        start: start,
        end: end
    };
}

function stringInsert(str, i, insert)
{
    return str.substring(0, i) + insert + str.substring(i);
}

// From http://stackoverflow.com/questions/263743/caret-position-in-textarea-in-characters-from-the-start
// Thanks to Tim Down for this code
function getCaretRange(el) {
    var start = 0, end = 0, normalizedValue, range,
        textInputRange, len, endRange;

    if (typeof el.selectionStart == "number" && typeof el.selectionEnd == "number") {
        start = el.selectionStart;
        end = el.selectionEnd;
    } else {
        range = document.selection.createRange();

        if (range && range.parentElement() == el) {
            len = el.value.length;
            normalizedValue = el.value.replace(/\r\n/g, "\n");

            // Create a working TextRange that lives only in the input
            textInputRange = el.createTextRange();
            textInputRange.moveToBookmark(range.getBookmark());

            // Check if the start and end of the selection are at the very end
            // of the input, since moveStart/moveEnd doesn't return what we want
            // in those cases
            endRange = el.createTextRange();
            endRange.collapse(false);

            if (textInputRange.compareEndPoints("StartToEnd", endRange) > -1) {
                start = end = len;
            } else {
                start = -textInputRange.moveStart("character", -len);
                start += normalizedValue.slice(0, start).split("\n").length - 1;

                if (textInputRange.compareEndPoints("EndToEnd", endRange) > -1) {
                    end = len;
                } else {
                    end = -textInputRange.moveEnd("character", -len);
                    end += normalizedValue.slice(0, end).split("\n").length - 1;
                }
            }
        }
    }

    return {
        start: start,
        end: end
    };
}

// From http://stackoverflow.com/questions/512528/set-cursor-position-in-html-textbox
// Thanks to kd7 and Roko C. Buljan
function setCaretPosition(elem, caretPos) {
    if(elem != null) {
        if(elem.createTextRange) {
            var range = elem.createTextRange();
            range.move("character", caretPos);
            range.select();
        }
        else {
            if(elem.selectionStart) {
                elem.focus();
                elem.setSelectionRange(caretPos, caretPos);
            }
            else
                elem.focus();
        }
    }
}
// Polyfill for function.bind()
// Thanks to the Mozilla foundation:
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Function/bind
if (!Function.prototype.bind) {
    Function.prototype.bind = function(oThis) {
        if (typeof this !== "function") {
            // closest thing possible to the ECMAScript 5
            // internal IsCallable function
            throw new TypeError("Function.prototype.bind - what is trying to be bound is not callable");
        }

        var aArgs   = Array.prototype.slice.call(arguments, 1),
            fToBind = this,
            fNOP    = function() {},
            fBound  = function() {
                return fToBind.apply(this instanceof fNOP
                     ? this
                     : oThis,
                     aArgs.concat(Array.prototype.slice.call(arguments)));
            };

        if (this.prototype) {
            // native functions don't have a prototype
            fNOP.prototype = this.prototype; 
        }
        fBound.prototype = new fNOP();

        return fBound;
    };
}

function escapeForRegexp(str) {
    return (str+"").replace(/[.?*+^$[\]\\(){}|-]/g, "\\$&");
}

function argDefault(arg, val) { return typeof arg !== 'undefined' ? arg : val; }

function ajax(url, callback, method, params, type) {
    method = argDefault(method, "GET");
    params = argDefault(params, null);
    type = argDefault(type, "json");

    if (params != null) {
        url += "?";
        first = true;
        for (var param in params) {
            if (!first) {
                url += "&"
            }
            url += encodeURIComponent(param) + "=" 
                + encodeURIComponent(params[param])
            first = false;
        }
    }

    req = new XMLHttpRequest();
    req.open(method, url);
    req.responseType = type;
    req.addEventListener("load", callback);
    req.send();
    return req;
}

function cloneNodeFull(node) {
    var result = node.cloneNode(true);
    result.onclick = node.onclick;
    return result;
}
