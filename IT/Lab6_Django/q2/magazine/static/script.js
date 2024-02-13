document.addEventListener('DOMContentLoaded', function () {
    const form = document.getElementById('cover-form');
    const frontCover = document.getElementById('front-cover');

    form.addEventListener('submit', function (event) {
        event.preventDefault();
        // Handle form submission and update front cover
        // Example: Get user input values and apply styles
        const bgColor = document.getElementById('bg-color').value;
        const fontSize = document.getElementById('font-size').value + 'px';
        const fontColor = document.getElementById('font-color').value;
        const greeting = document.getElementById('greeting').value;
        const borderStyle = document.querySelector('input[name="border-style"]:checked').value;
        const showImage = document.getElementById('show-image').checked;

        frontCover.style.backgroundColor = bgColor;
        frontCover.style.fontSize = fontSize;
        frontCover.style.color = fontColor;
        frontCover.style.border = `2px ${borderStyle} black`;
        frontCover.textContent = greeting;

        if (showImage) {
            frontCover.style.backgroundImage = `url("C:\Users\IT\Desktop\ITlab210905272\Lab6_Django\q2\magazine\static\image.jpg")`;
        } else {
            // Hide cover image
            frontCover.style.backgroundImage = 'none';
        }
    });
});
