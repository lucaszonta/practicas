function runDemo() {
    var el = updateTransition();

    el.addEventListener("transitionend", updateTransition, true);
}

function updateTransition() { 
    var el = document.querySelector("div.slideLeft");
    
    if (el) { 
            el.className = "slideRight";
    } else { 
        el = document.querySelector("div.slideRight"); 
    el.className = "slideLeft"; 
    }

    return el; 
}