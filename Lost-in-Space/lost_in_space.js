"use strict";
// Fonction de construction des éléments
function Elements( filename, left, top) {
  this.element = document.createElement( "img" );
  this.element.src = filename;
  this.element.style.position = "absolute";
  document.body.appendChild( this.element );


  
  // Propriété de la position gauche d'un élément
  Object.defineProperty( this, "left", {
    get: function() {
      return this._left;
    },
    set: function( value ) {
      this._left = value;
      this.element.style.left = value + "px";
    }
  } );

    // Propriété de la position haute d'un élément
    Object.defineProperty( this, "top", {
      get: function() {
        return this._top;
      },
      set: function( value ) {
        this._top = value;
        this.element.style.top = value + "px";
      }
    } );

  // Propriété de l'affichage d'un élément
  Object.defineProperty( this, "display", {
    get: function() {
      return this.element.style.display;
    },
    set: function( value ) {
      this.element.style.display = value;
    }
  } );

  this.left = left;
  this.top = top;

  // Animation Missile/Alien
  Elements.prototype.startAnimation = function( fonction, interval) {
    if ( this._clock ) window.clearInterval( this._clock );
    var _this = this;
    this._clock = window.setInterval( function() {
      fonction( _this );
    }, interval );
  };

  Elements.prototype.stopAnimation = function() {
    window.clearInterval( this._clock );
  };

  Elements.prototype.collision = function (other){
    return ! ( (this.top + this.element.height < other.top) ||
               this.top > (other.top + other.element.height) ||
               (this.left + this.element.width < other.left) ||
               this.left > (other.left + other.element.width) );
  };
};

window.onload = function() {
  // TODO !!
};