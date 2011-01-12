class User < ActiveRecord::Base
  has_many :group, :foreign_key => "creator_id"
  has_many :adminship, :dependent => :destroy #group adminship
  has_many :membership, :dependent => :destroy #group membership
  
  # Warning! These are only the recommendations the user created.
  # Refer to User.memberships.group.recommendations for all recommendations
  # related to this user
  has_many :recommendation, :foreign_key => "admin_id"
  
  has_many :event, :foreign_key => "creator_id"
  has_many :acceptance, :dependent => :destroy #event acceptance
  has_many :reject, :dependent => :destroy #event reject
  
  has_many :invitor_relation, :foreign_key => :destroy
  has_many :invitee_relation, :foreign_key => :destroy
end
