const navSlide = () => {
    const burger = document.querySelector('.burger');
    const nav = document.querySelector('.nav-links');
    const navLinks = document.querySelectorAll('.nav-links li');

    //Toggle Nav
    burger.addEventListener('click', () =>{
        nav.classList.toggle('nav-active');

      //Animate Links
      navLinks.forEach((link, index) => {
        if(link.style.animation) {
          link.style.animation = '';
        }
        else {
          link.style.animation = `navLinkFade 0.5s ease forwards ${index / 6 + 1}s`;
        }
      });

      //Burger Animation
      burger.classList.toggle('toggle');
    });
}

//const app = ()=> {
  navSlide();

//}


/* When the user clicks on the button,
toggle between hiding and showing the dropdown content */
/*function dropDown() {
  document.getElementById("myDropdown").classList.toggle("show");
}

// Close the dropdown if the user clicks outside of it
window.onclick = function(event) {
  if (!event.target.matches('.dropbtn')) {
    var dropdowns = document.getElementsByClassName("dropdown-content");
    var i;
    for (i = 0; i < dropdowns.length; i++) {
      var openDropdown = dropdowns[i];
      if (openDropdown.classList.contains('show')) {
        openDropdown.classList.remove('show');
      }
    }
  }
}*/



