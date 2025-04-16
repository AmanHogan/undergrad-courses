/**
 * Author: Aman Hogan Bailey
 * Sends yelp ai request and gets 
 * best 10 businesses matching query
 * 
 */


/**
 * Inits js
 */
function initialize () 
{

}

/**
 * Gets values in search, term, and level input and puts 
 * this information into a query to send into an api request.
 * @returns Formatted query string for php query
 */
function getQueryString() 
{
   var formattedTermValue = document.getElementById("term").value.trim().toLowerCase().replace(/[\s,]+/g, '+');
   var formattedCityValue = document.getElementById("city").value.trim().toLowerCase().replace(/[\s,]+/g, '+');
   var levelLimitValue = document.getElementById("level").value;
   var queryString = "proxy.php?term=" + formattedTermValue + "&location=" + formattedCityValue + "&limit=" + levelLimitValue;
   return queryString
}

/**
 * Finds best restaurants using yelp api service and displays results in html.
 */
function findRestaurants () 
{
   var xhr = new XMLHttpRequest();
   const qString = getQueryString(); 
   
   // Call yelp api
   xhr.open("GET", qString);
   xhr.setRequestHeader("Accept","application/json");
   xhr.onreadystatechange = function ()
	{
		if (this.readyState == 4) 
      	{
			var json = JSON.parse(this.responseText);

			// Results were found
			if (json.businesses && json.businesses.length > 0) 
			{
				console.log(json.businesses);
				displayResults(json.businesses);
			}

			// No businesses found
			else
			{
				let outputDiv = document.getElementById('output');
				outputDiv.innerHTML = '<p>No businesses found for the given query.</p>';
			}
      	}
   	};
   	xhr.send(null);
}

/**
 * Displays yelp api request results
 * @param {Array} businesses array of objects 
 * containing details about yelp request 
 */
async function displayResults(businesses)
{
   // Clear previous results
   let outputDiv = document.getElementById('output');
   outputDiv.innerHTML = '';

   	// Create ordered list
	const orderedList = document.createElement('ol');
	orderedList.style.paddingLeft = '20px'; 
   
	// Sort by rating (best business is 1)
	businesses.sort((a, b) => b.rating - a.rating);

	// Limit results to top 10 or less if less than 10 results
	const numResults = Math.min(businesses.length, 10);

	for (let i = 0; i < numResults; i++)
	{
		let business = businesses[i];

		// Create list item
		const listItem = document.createElement('li');
		listItem.style.marginBottom = '20px';

		// Create a card
		let card = document.createElement('div');
		card.style.border = "solid";
		card.style.padding = "15px";
		card.style.margin = "10px 50px 0px";
		card.style.boxShadow = "0 4px 8px 0 rgba(0, 0, 0, 0.1)";

		// Details container
		const details = document.createElement('div');
		details.style.flex = '1';
		
		// Add rank 
		let rankingText = document.createElement('h2');
		rankingText.innerHTML = `Match: ${i+1}`;
		card.appendChild(rankingText);

		// Image
		let img = document.createElement('img');
		img.src = business.image_url;
		img.alt = `${business.name} image`;
		img.style.width = "100px";
		card.appendChild(img);
		
		// Name and Link
		let nameLink = document.createElement('a');
		nameLink.href = business.url;
		nameLink.target = "_blank";
		nameLink.innerHTML = business.name;
		nameLink.style.display = "block";
		card.appendChild(nameLink);
		
		// Categories
		let categories = business.categories.map(cat => cat.title).join(', ');
		let categoriesText = document.createElement('p');
		categoriesText.innerHTML = `Categories: ${categories}`;
		card.appendChild(categoriesText);
		
		// Price, Price sometimes isn't included for some reason
		if (business.price) 
		{
			let priceText = document.createElement('p');
			priceText.innerHTML = `Price: ${business.price}`;
			card.appendChild(priceText);
		}
		
		// Rating
		let ratingText = document.createElement('p');
		ratingText.innerHTML = `Rating: ${business.rating} / 5`;
		card.appendChild(ratingText);
		
		// Address, formatted
		let addressText = document.createElement('p');
		addressText.innerHTML = `Address: ${business.location.address1}, ${business.location.city}, ${business.location.zip_code}`;
		card.appendChild(addressText);
		
		// Phone number
		let phoneText = document.createElement('p');
		phoneText.innerHTML = `Phone: ${business.display_phone}`;
		card.appendChild(phoneText);

		// Append details to card
		card.appendChild(details);
		listItem.appendChild(card);
		orderedList.appendChild(listItem);
	}

	outputDiv.appendChild(orderedList);
}
