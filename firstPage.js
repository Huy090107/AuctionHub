const findButton = document.getElementById("findButton");

const locationInput = document.getElementById("location");

const locationSuggestions = document.getElementById("locationSuggestions");

const budgetInput = document.getElementById("budget");

// ---------------- Location suggestions ----------------

const locations = [
  {
    name: "Đại học Công nghệ Kỹ thuật TP.HCM",
  },

  {
    name: "Đại học Sư phạm Kỹ thuật TP.HCM",
  },

  {
    name: "Vincom Plaza Lê Văn Việt",
  },

  {
    name: "Làng Đại học Quốc gia TP.HCM",
  },

  {
    name: "Đại học Văn Lang",
  },

  {
    name: "Đại học Bách Khoa TP.HCM",
  },
];

// ---------------- Location search ----------------

locationInput.addEventListener("input", function () {
  const text = locationInput.value.trim().toLowerCase();

  locationSuggestions.innerHTML = "";

  if (text === "") {
    return;
  }

  const results = locations.filter(function (location) {
    return location.name.toLowerCase().includes(text);
  });

  results.forEach(function (location) {
    const item = document.createElement("div");

    item.className = "suggestion-item";

    item.textContent = location.name;

    item.addEventListener("click", function () {
      locationInput.value = location.name;

      locationSuggestions.innerHTML = "";
    });

    locationSuggestions.appendChild(item);
  });
});

// ---------------- Budget formatting ----------------

// Format budget when leaving the input

budgetInput.addEventListener("blur", function () {
  let value = budgetInput.value.replace(/\D/g, "");

  if (value === "") {
    budgetInput.value = "";

    return;
  }

  budgetInput.value = Number(value).toLocaleString("vi-VN");
});

// ---------------- Find places ----------------

findButton.addEventListener("click", function () {
  const location = locationInput.value.trim();

  const category = document.getElementById("category").value;

  const budgetText = budgetInput.value;

  const distanceText = document.getElementById("distance").value;

  // Convert "100.000" -> 100000

  const budget = Number(budgetText.replace(/\D/g, ""));

  const distance = Number(distanceText);

  // Check location

  if (location === "") {
    alert("Please enter your location.");

    return;
  }

  // Check budget

  if (budgetText === "" || isNaN(budget) || budget < 0) {
    alert("Please enter a valid budget.");

    return;
  }

  // Check distance

  if (distanceText === "" || isNaN(distance) || distance < 0) {
    alert("Please enter a valid distance.");

    return;
  }

  // Display data in console

  console.log("Location:", location);

  console.log("Category:", category);

  console.log("Budget:", budget);

  console.log("Distance:", distance);

  // Show result

  alert(
    "Location: " +
      location +
      "\nCategory: " +
      category +
      "\nBudget: " +
      budget.toLocaleString("vi-VN") +
      " VND" +
      "\nMax distance: " +
      distance +
      " km",
  );
});
